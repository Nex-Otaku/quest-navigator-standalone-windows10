#include "utils.h"
#include "..\..\face\standalone-win10\Constants.h"
#include "..\..\core\files.h"
#include "..\..\core\configuration.h"
#include "..\..\core\dialogs.h"
#ifdef _WIN32
//#include <shlwapi.h>
#include <Shlobj.h>
#endif

//#include <Awesomium/STLHelpers.h>
#include <vector>
#include <algorithm>
//#include "../deps/md5/md5.h"

//using namespace Awesomium;

#define LOAD_XML_ATTRIB(name, configLine) if (valid) { valid = Configuration::loadXmlAttrib(root, name, configLine); }

/*

Везде используем string, в нём хранятся юникодовые строки в UTF-8.

В исходном файле строки с русским текстом, заданные явно, тоже хранятся в UTF-8.
Visual Studio 2012 умеет определять кодировку исходного файла, с этим проблем быть не должно.

При передаче в движок Awesomium преобразовываем в WebString функцией ToWebString.

При получении из WinApi:

1. Если возвращается указатель на PTSTR или LPWSTR 
(в нашей конфигурации одно и тоже, т.к. включен Юникод)
то просто сохраняем в wstring.
Потом конвертируем в string в UTF-8 функцией narrow.
Пример:
wstring wCmd = GetCommandLine();
string cmd = narrow(wCmd);

2. Если возвращается в буфер из TCHAR, 
то также просто сохраняем в wstring простым присваиванием указателя на начало буфера.
Потом конвертируем в string в UTF-8 функцией narrow.
Пример:
TCHAR szString[1024];
PTSTR szUrl = szString;
...
UrlCreateFromPath(FileName, szUrl, &sUrl, NULL); 
wstring wUrl = szUrl;
string url = narrow(wUrl);

При получении строк из интерпретатора пользуемся функцией fromQsp.

*/

namespace QuestNavigator {

	// Загрузка конфигурации плеера
	// См. ConfigurationBuilder
	//bool initOptions(string contentPath)
	//{
		//// Устанавливаем параметры по умолчанию
		//Configuration::setBool(ecpSoundCacheEnabled, false);
		//Configuration::setInt(ecpSaveSlotMax, 5);
		//Configuration::setString(ecpDefaultSkinName, DEFAULT_SKIN_NAME);
		//Configuration::setBool(ecpLimitSingleInstance, false);
		//Configuration::setString(ecpCacheDir, "");

		//// Разбираем параметры запуска
		//int argCount = 0;
		//LPWSTR* szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
		//if (szArgList == NULL) {
		//	showError("Не могу прочесть аргументы командной строки");
		//	return false;
		//}
		//vector<string> params;
		//for (int i = 0; i < argCount; i++) {
		//	params.push_back(trim(narrow(szArgList[i])));
		//}
		//LocalFree(szArgList);
		//bool contentPathSet = contentPath != "";
		//bool contentPathFound = false;
		//for (int i = 0; i < argCount; i++) {
		//	string param = params[i];
		//	// Если мы вызываем программу из командной строки,
		//	// то первым параметром идёт имя exe-файла, игнорируем его.
		//	if (endsWith(param, ".exe"))
		//		continue;
		//	bool isOption = startsWith(param, "-");
		//	// Нам передали путь к файлу игры в командной строке.
		//	// Просто сохраняем его, проверять будем позже,
		//	// когда убедимся что строка параметров разобрана правильно.
		//	if (!contentPathFound && !isOption) {
		//		// Если нам заранее известен путь к файлу игры, 
		//		// то мы игнорируем путь, указанный в командной строке.
		//		// Типичная ситуация - выбор произвольной игры в "Полке игр".
		//		// При запуске плеера указана одна игра, а нам теперь нужна другая.
		//		if (!contentPathSet) {
		//			contentPath = param;
		//			contentPathSet = true;
		//		}
		//		contentPathFound = true;
		//	} else if (isOption) {
		//		// Разбираем опции
		//		if (param == OPTION_ENABLE_SOUND_CACHE) {
		//			// Кэшировать ли звуковые файлы.
		//			Configuration::setBool(ecpSoundCacheEnabled, true);
		//		} else if (startsWith(param, OPTION_DEFAULT_SKIN)) {
		//			// Какой из стандартных шаблонов выбирать по умолчанию для игры, 
		//			// при отсутствии у игры своего шаблона, 
		//			// и отсутствии указаний в конфиге игры.
		//			if (i + 1 == argCount) {
		//				showError("Не указано имя шаблона для опции " + OPTION_DEFAULT_SKIN);
		//			}
		//			Configuration::setString(ecpDefaultSkinName, params[i + 1]);
		//			i++;
		//		} else if (param == OPTION_RESTART) {
		//			// Убить "старые" окна плеера.
		//			// Используется при редактировании игры, 
		//			// чтобы запускать обновлённую версию 
		//			// без закрытия плеера с предыдущей версией вручную.
		//			Configuration::setBool(ecpLimitSingleInstance, true);
		//		} else {
		//			showError("Неизвестная опция: [" + param + "]");
		//			return false;
		//		}
		//	} else {
		//		showError("Неизвестный параметр: [" + param + "]\n" +
		//			"Возможно, путь к файлу содержит пробелы и вы забыли взять его в кавычки.");
		//		return false;
		//	}
		//}
		//// Всё разобрано правильно.

		//// Определяем игру для запуска.
		//// 1. Если игра указана параметром командной строки, запускаем её.
		//// 2. Если параметр не указан, ищем игру в папке плеера.
		//// 3. Если в папке плеера игра не найдена, игра запускается из assets\standalone_content

		//string contentDir = "";
		//string skinFilePath = "";
		//string gameFileName = "";
		//string gameFilePath = "";
		//string configFilePath = "";
		//string saveDir = "";
		//string windowTitle = QN_APP_NAME + " " + QN_VERSION;
		//bool runningDefaultGame = false;
		//if (contentPathSet) {
		//	// Нам передали путь к игре.
		//	// Всего три варианта:
		//	// 1. Это путь к архиву .qn;
		//	// 2. Это путь к файлу .qsp;
		//	// 3. Это путь к папке игры.
		//	// Проверяем путь на существование и читаемость.

		//	bool bValidDirectory = dirExists(contentPath);
		//	bool bValidFile = !bValidDirectory && fileExists(contentPath);
		//	// Путь к файлу игры должен быть абсолютным.
		//	// Если он будет относительным,
		//	// библиотека не сможет правильно загрузить QSP-модули.
		//	if (bValidFile || bValidDirectory) {
		//		contentPath = relativePathToAbsolute(contentPath);
		//	}
		//	if (bValidFile) {
		//		// Проверяем расширение файла
		//		bool bExtQn = endsWith(contentPath, ".qn");
		//		bool bExtQsp = endsWith(contentPath, ".qsp");
		//		if (!bExtQn && !bExtQsp) {
		//			showError("Неизвестный формат файла!\nПоддерживаемые форматы: qn, qsp");
		//			return false;
		//		}
		//		if (bExtQn) {
		//			// STUB
		//			showError("Загрузка архива qn ещё не реализована.");
		//			return false;
		//		} else {
		//			// Сохраняем путь к файлу игры
		//			gameFilePath = contentPath;
		//			gameFileName = contentPath;
		//			// Вычисляем путь к папке игры
		//			if (contentPath.length() > 0) {
		//				int pos = contentPath.find_last_of(PATH_DELIMITER);
		//				if  (pos != string::npos) {
		//					contentDir = contentPath.substr(0, pos);
		//					gameFileName = contentPath.substr(pos + 1);
		//				}
		//			}
		//			// Вычисляем пути к необходимым файлам
		//			skinFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_SKIN_FILE);
		//			configFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_CONFIG_FILE);
		//		}
		//		// STUB
		//	} else if (bValidDirectory) {
		//		// Сохраняем путь к папке игры.
		//		// Если в указанной папке есть вложенная папка "standalone_content",
		//		// то считаем её папкой игры. Иначе считаем папкой игры указанную папку.
		//		string deepDir = contentPath + PATH_DELIMITER + DEFAULT_CONTENT_REL_PATH;
		//		if (dirExists(deepDir)) {
		//			contentDir = deepDir;
		//		} else {
		//			contentDir = contentPath;
		//		}

		//		// Вычисляем пути к необходимым файлам
		//		skinFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_SKIN_FILE);
		//		// Определяем файл игры (*.qsp) в указанной папке.
		//		if (!findGameFile(contentDir, gameFileName))
		//			return false;
		//		gameFilePath = getRightPath(contentDir + PATH_DELIMITER + gameFileName);
		//		configFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_CONFIG_FILE);
		//	} else {
		//		DWORD error = GetLastError();
		//		if (error == ERROR_FILE_NOT_FOUND) {
		//			showError("Не найден файл: [" + contentPath + "]");
		//		} else if (error == ERROR_PATH_NOT_FOUND) {
		//			showError("Не найден путь: [" + contentPath + "]");
		//		} else {
		//			showError("Не удалось прочесть файл: [" + contentPath + "]");
		//		}
		//		return false;
		//	}
		//}
		//
		//if (contentDir == "") {
		//	// Запускаем игру по умолчанию
		//	runningDefaultGame = true;
		//	string assetsDir = getPlayerDir() + PATH_DELIMITER + ASSETS_DIR;
		//	configFilePath = getRightPath(assetsDir + PATH_DELIMITER 
		//		+ DEFAULT_CONTENT_REL_PATH + PATH_DELIMITER 
		//		+ DEFAULT_CONFIG_FILE);
		//	contentDir = assetsDir + PATH_DELIMITER + DEFAULT_CONTENT_REL_PATH;
		//	// Определяем файл игры (*.qsp) в указанной папке.
		//	if (!findGameFile(contentDir, gameFileName))
		//		return false;
		//	gameFilePath = contentDir + PATH_DELIMITER + gameFileName;
		//	skinFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_SKIN_FILE);
		//}

		//// Приводим путь к файлу игры в каноничную форму.
		//gameFilePath = canonicalizePath(gameFilePath);
		//
		//// Считаем уникальный хэш игры.
		//string gameHash = md5(gameFilePath);

		//// Папка для сохранений
		//saveDir = "";
		//// Путь к пользовательской папке "Мои документы"
		//WCHAR wszPath[MAX_PATH];
		//HRESULT hr = SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, wszPath);
		//if (hr != S_OK) {
		//	showError("Не удалось получить путь к папке \"Мои документы\".");
		//	return false;
		//}
		//saveDir = getRightPath(narrow(wszPath) + PATH_DELIMITER + DEFAULT_SAVE_REL_PATH + PATH_DELIMITER + gameHash);

		//// Папка с данными приложения.
		//// В ней находится БД, а также кэшированные игры.
		//hr = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, wszPath);
		//if (hr != S_OK) {
		//	showError("Не удалось получить путь к папке \"Application Data\".");
		//	return false;
		//}
		//string appDataDir = narrow(wszPath) + PATH_DELIMITER + APP_DATA_DIR;

		//// Приводим все пути к каноничной форме.
		//contentDir = canonicalizePath(contentDir);
		//skinFilePath = canonicalizePath(skinFilePath);
		//configFilePath = canonicalizePath(configFilePath);
		//saveDir = canonicalizePath(saveDir);
		//appDataDir = canonicalizePath(appDataDir);

		//// Проверяем все файлы на читаемость
		//if (!fileExists(skinFilePath))
		//	skinFilePath = "";
		//if (!fileExists(configFilePath))
		//	configFilePath = "";
		//if (!fileExists(gameFilePath)) {
		//	showError("Не удалось загрузить игру из файла: " + gameFilePath);
		//	return false;
		//}

		//// Сохраняем конфигурацию
		//Configuration::setString(ecpContentDir, contentDir);
		//Configuration::setString(ecpSkinFilePath, skinFilePath);
		//Configuration::setString(ecpGameFilePath, gameFilePath);
		//Configuration::setString(ecpGameHash, gameHash);
		//Configuration::setString(ecpGameFileName, gameFileName);
		//Configuration::setString(ecpConfigFilePath, configFilePath);
		//Configuration::setString(ecpSaveDir, saveDir);
		//Configuration::setString(ecpAppDataDir, appDataDir);
		//Configuration::setString(ecpWindowTitle, windowTitle);
		//Configuration::setBool(ecpIsFullscreen, false);
		//Configuration::setBool(ecpRunningDefaultGame, runningDefaultGame);

		//// Загружаем настройки игры из файла config.xml
		//bool gameConfigLoaded = loadGameConfig();
		//if (!gameConfigLoaded)
		//	return false;

		//return true;



		// STUB
	//	return true;
	//}

	// Загружаем настройки игры из файла config.xml
	// См. ConfigurationBuilder
	//bool loadGameConfig()
	//{
	//	// Устанавливаем настройки по умолчанию
	//	Configuration::setInt(ecpGameWidth, 800);
	//	Configuration::setInt(ecpGameHeight, 600);
	//	Configuration::setInt(ecpGameMinWidth, 0);
	//	Configuration::setInt(ecpGameMinHeight, 0);
	//	Configuration::setInt(ecpGameMaxWidth, 0);
	//	Configuration::setInt(ecpGameMaxHeight, 0);
	//	Configuration::setString(ecpGameTitle, Configuration::getString(ecpGameFileName));
	//	Configuration::setBool(ecpGameResizeable, true);
	//	Configuration::setBool(ecpGameFullscreenAvailable, true);
	//	Configuration::setBool(ecpGameStartFullscreen, false);
	//	Configuration::setString(ecpSkinName, "");
	//	Configuration::setBool(ecpGameIsStandalone, false);

	//	string configFilePath = Configuration::getString(ecpConfigFilePath);
	//	// Если файл не найден, то всё в порядке,
	//	// просто оставляем дефолтные настройки.
	//	if (!fileExists(configFilePath))
	//		return true;

	//	TiXmlDocument doc;
	//	// Читаем файл в память
	//	void* buffer = NULL;
	//	int bufferLength = 0;
	//	if (!loadFileToBuffer(configFilePath, &buffer, &bufferLength)) {
	//		showError("Не удалось прочесть файл \"" + configFilePath + "\".");
	//		return false;
	//	}
	//	// Разбираем XML
	//	doc.Parse((const char*)buffer, 0, TIXML_ENCODING_UTF8);
	//	delete buffer;
	//	if (doc.Error())
	//	{
	//		showError("Не удалось загрузить XML-структуру из файла \"" + configFilePath + "\".");
	//		return false;
	//	}
	//	TiXmlElement* root = doc.FirstChildElement();
	//	if (root == NULL)
	//	{
	//		showError("Не найден корневой элемент конфигурационного файла \"" + configFilePath + "\".");
	//		return false;
	//	}

	//	bool valid = true;
	//	LOAD_XML_ATTRIB("width", ecpGameWidth);
	//	LOAD_XML_ATTRIB("height", ecpGameHeight);
	//	LOAD_XML_ATTRIB("minWidth", ecpGameMinWidth);
	//	LOAD_XML_ATTRIB("minHeight", ecpGameMinHeight);
	//	LOAD_XML_ATTRIB("maxWidth", ecpGameMaxWidth);
	//	LOAD_XML_ATTRIB("maxHeight", ecpGameMaxHeight);
	//	LOAD_XML_ATTRIB("title", ecpGameTitle);
	//	LOAD_XML_ATTRIB("resizeable", ecpGameResizeable);
	//	LOAD_XML_ATTRIB("fullscreenAvailable", ecpGameFullscreenAvailable);
	//	LOAD_XML_ATTRIB("startFullscreen", ecpGameStartFullscreen);
	//	LOAD_XML_ATTRIB("skinName", ecpSkinName);
	//	LOAD_XML_ATTRIB("standalone", ecpGameIsStandalone);
	//	if (!valid) {
	//		return false;
	//	}

	//	// Обрабатываем настройки игры
	//	if (Configuration::getBool(ecpGameFullscreenAvailable) && 
	//		Configuration::getBool(ecpGameStartFullscreen)) {
	//			Configuration::setBool(ecpIsFullscreen, true);
	//	}
	//	string gameTitle = Configuration::getString(ecpGameTitle);
	//	if (gameTitle != "") {
	//		Configuration::setString(ecpWindowTitle, gameTitle);
	//	}

	//	return true;
	//}

	// Получаем идентификатор для мьютекса.
	string getInstanceMutexId()
	{
		string gameFileMd5 = Configuration::getString(ecpGameHash);
		string mutexId = QN_APP_GUID + gameFileMd5;
		return mutexId;
	}

	// Выводим текст в консоль.
	void writeConsole(HWND hWnd, string text)
	{
		//// Мы передаём текст в другое приложение,
		//// специально созданное для отображения лога.

		//// Правильнее передавать текст в стандартный поток вывода,
		//// но это не получилось. 
		//// Может быть, в будущем будет исправлено.

		//// Преобразовываем текст в виндовый формат.
		//wstring wText = widen(text);
		//// Заполняем структуру для передачи данных.
		//COPYDATASTRUCT cds;
		//cds.dwData = (ULONG_PTR)eidtLog;
		//cds.cbData = ((DWORD)wText.length() + 1)*sizeof(wchar_t);
		//cds.lpData = (PVOID)wText.c_str();
		//HWND hwndSender = hWnd;
		//HWND hwndReceiver = FindWindow(szLogWindowClass, NULL);
		//if (hwndReceiver == NULL) {
		//	// Нет окна для логирования - просто выходим.
		//	return;
		//}
		//LRESULT res = SendMessage(hwndReceiver, WM_COPYDATA, (WPARAM)hwndSender, (LPARAM)&cds);
		//if (res != TRUE) {
		//	showError("Ошибка при отправке сообщения окну логирования");
		//}
	}


	DWORD getWindowStyle() {
		return Configuration::getBool(ecpGameResizeable) ? WS_OVERLAPPEDWINDOW :
			(WS_OVERLAPPED     | 
			WS_CAPTION        | 
			WS_SYSMENU        | 
			WS_MINIMIZEBOX);
	}

	// Переключение полноэкранного режима.
	//WINDOWPLACEMENT wpc;
	void toggleFullscreenByHwnd(HWND hWnd) {
		setFullscreenByHwnd(hWnd, !Configuration::getBool(ecpIsFullscreen));
	}
	// Установка полноэкранного режима.
	void setFullscreenByHwnd(HWND hWnd, bool fullscreen) {
		//if (!fullscreen) {
		//	// Из всего экрана в оконное                                      
		//	// Устанавливаем стили оконного режима
		//	SetWindowLong(hWnd, GWL_STYLE, getWindowStyle());
		//	// Загружаем парметры предыдущего оконного режима
		//	SetWindowPlacement(hWnd, &wpc);
		//	// Показываем обычное окно
		//	ShowWindow(hWnd, SW_SHOWNORMAL);

		//	Configuration::setBool(ecpIsFullscreen, false);
		//} else if (Configuration::getBool(ecpGameFullscreenAvailable)) {
		//	// Сохраняем параметры оконного режима
		//	GetWindowPlacement(hWnd, &wpc);
		//	// Устанавливаем новые стили
		//	SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
		//	SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);
		//	// Окно во весь экран
		//	ShowWindow(hWnd, SW_SHOWMAXIMIZED);

		//	Configuration::setBool(ecpIsFullscreen, true);
		//}
	}
}