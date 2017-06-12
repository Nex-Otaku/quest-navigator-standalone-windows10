#include "game_files.h"
#include "..\..\face\standalone-win10\Constants.h"
#include "..\..\core\configuration.h"
#include "..\..\core\files.h"
#include "..\..\core\dialogs.h"

namespace QuestNavigator {
	// Готовим игру к запуску.
	bool prepareGameFiles()
	{
		// Основной алгоритм обработки файлов:
		// 1. Если в корне архива или в корне указанной локальной папки 
		//    есть папка standalone_content, 
		//    то корневой папкой игры считается она,
		//    иначе - корневой папкой игры считается корень архива 
		//    или указанной локальной папки.
		// 2. Проверяем наличие и читаемость скина игры.
		// 3. Проверяем наличие папки "qsplib" уровнем выше корневой папки игры.
		// 4. Если есть файл скина и есть папка "qsplib", то запускается игра.
		// 5. Иначе, создаётся временная папка, в которую копируются:
		// 5.1 - файлы оформления игры - .js, .css, картинки;
		// 5.2 - файл скина (если есть в папке игры - то скин игры, 
		//                   иначе дефолтный либо один из стандартных, 
		//                   указанный в config.xml)
		// 5.3 - папка "qsplib".
		// 6. Запускается игра со скином из временной папки.

		// В режиме "standalone" ничего не копируем, всё уже должно быть на своих местах.
		bool bStandalone = Configuration::getBool(ecpGameIsStandalone);

		// Если плеер запущен не в режиме standalone,
		// то нам потребуется папка данных.
		string appDataDir = Configuration::getString(ecpAppDataDir);
		// Если папка ещё не существует, создаём.
		if (!bStandalone) {
			if (!buildDirectoryPath(appDataDir)) {
				showError("Не удалось создать папку данных для плеера: " + appDataDir);
				return false;
			}
		}

		bool bCopyQsplib = false;
		bool bCopySkin = false;
		// Если настройка "ContentDir" не задана, 
		// значит игру не нашли.
		// Тогда используем "игру" по умолчанию из папки "assets\standalone_content".
		string contentDir = Configuration::getString(ecpContentDir);
		string skinFilePath = Configuration::getString(ecpSkinFilePath);
		string selectedSkin = Configuration::getString(ecpDefaultSkinName);
		string gameFilePath = Configuration::getString(ecpGameFilePath);
		string gameHash = Configuration::getString(ecpGameHash);
		string assetsDir = getPlayerDir() + PATH_DELIMITER + ASSETS_DIR;
		// Проверяем наличие qsplib.
		string gameQsplibDir = contentDir + PATH_DELIMITER + ".." + PATH_DELIMITER + QSPLIB_DIR;
		bCopyQsplib = !dirExists(gameQsplibDir);

		// Проверяем наличие скина.
		bCopySkin = skinFilePath == "";
		if (bCopySkin) {
			// Выясняем, какой скин был указан для игры.
			string configSkin = Configuration::getString(ecpSkinName);
			if (configSkin != "") {
				// Выбираем указанный скин.
				selectedSkin = configSkin;
			}
		}

		// Требуется копирование.
		if (bCopyQsplib || bCopySkin) {
			// Если в игре включен режим "standalone",
			// то выводим ошибку и завершаем работу.
			if (bStandalone) {
				string error = "Ошибка: при включенном режиме \"standalone\" отсутствует "
					+ (bCopyQsplib ? "папка \"" + QSPLIB_DIR + "\"." : "шаблон оформления.");
				showError(error);
				return false;
			}

			// Проверяем наличие папки "assets", 
			// внутри которой лежат необходимые папки шаблонов оформления, 
			// "qsplib" и файл игры по умолчанию.
			if (!dirExists(assetsDir)) {
				showError("Не найдена папка \"" + assetsDir + "\" системных файлов плеера.");
				return false;
			}

			// Создаём временную папку для игры.
			string gameFolder = getRightPath(appDataDir + PATH_DELIMITER + GAME_CACHE_DIR + PATH_DELIMITER + gameHash);
			gameFolder = canonicalizePath(gameFolder);
			if (!buildDirectoryPath(gameFolder)) {
				showError("Не удалось создать временную папку для игры: " + gameFolder);
				return false;
			}
			Configuration::setString(ecpCacheDir, gameFolder);
			string contentFolder = gameFolder + PATH_DELIMITER + DEFAULT_CONTENT_REL_PATH;
			if (!buildDirectoryPath(contentFolder)) {
				showError("Не удалось создать папку для содержимого игры: " + contentFolder);
				return false;
			}

			// Копируем qsplib.
			// true - из базовых файлов, false - из папки игры.
			string source = bCopyQsplib ?
				assetsDir + PATH_DELIMITER + QSPLIB_DIR : gameQsplibDir;
			string dest = gameFolder + PATH_DELIMITER + QSPLIB_DIR;
			if (!copyFileTree(source, dest)) {
				showError("Не удалось скопировать папку библиотеки из \"" + source + "\" в \"" + dest + "\".");
				return false;
			}

			// Копируем скин.
			string destSkinFile = contentFolder + PATH_DELIMITER + DEFAULT_SKIN_FILE;
			if (bCopySkin) {
				// Копируем из базовых файлов

				string skinsDir = assetsDir + PATH_DELIMITER + SKINS_DIR;

				// Заполняем список существующих скинов.
				vector<string> skinsList;
				if (!getFoldersList(skinsDir, skinsList))
					return false;

				// Ищем указанный скин среди существующих.
				bool found = false;
				for (int i = 0; i < (int)skinsList.size(); i++)
				{
					if (skinsList[i] == selectedSkin) {
						found = true;
						break;
					}
				}

				// Если не найден, выходим.
				if (!found) {
					showError("Не найден шаблон оформления " + selectedSkin);
					return false;
				}

				// Копируем все файлы из папки шаблона
				string source = skinsDir + PATH_DELIMITER + selectedSkin;
				if (!copyFileTree(source, contentFolder)) {
					showError("Не удалось скопировать шаблон оформления из \"" +
						source + "\" в \"" + contentFolder + "\".");
					return false;
				}
			}
			else {
				// Копируем из папки игры
				if (!copyFile(skinFilePath, destSkinFile)) {
					showError("Не удалось скопировать файл шаблона оформления из \"" +
						skinFilePath + "\" в \"" + destSkinFile + "\".");
					return false;
				}
			}
			// Обновляем переменную окружения
			Configuration::setString(ecpSkinFilePath, destSkinFile);

			// Копируем все файлы, которые могут понадобиться браузеру.
			vector<string> masks;
			// Картинки - ".jpg", ".jpeg", ".gif", ".bmp", ".png".
			masks.push_back("*.jpg");
			masks.push_back("*.jpeg");
			masks.push_back("*.gif");
			masks.push_back("*.bmp");
			masks.push_back("*.png");
			masks.push_back("*.cur");
			masks.push_back("*.ani");
			// Стили и скрипты - ".css", ".js".
			// Если bCopySkin == false, значит, мы используем скин из папки игры.
			// Поэтому копируем из папки игры CSS и JS файлы.
			if (!bCopySkin) {
				masks.push_back("*.css");
				masks.push_back("*.js");
			}
			// Проходим по всем расширениям.
			for (int i = 0; i < (int)masks.size(); i++) {
				if (!copyFileTree(contentDir, contentFolder, masks[i])) {
					showError("Не удалось переместить файлы с маской \"" + masks[i] +
						"\" из \"" + contentDir + "\" в \"" + contentFolder + "\"");
					return false;
				}
			}
		}
		return true;
	}
}