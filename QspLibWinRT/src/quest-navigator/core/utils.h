#pragma once

#include <string>
#include <vector>
#include <Windows.h>
//#include <Awesomium/WebString.h>
#include "../../deps/qsp/qsp.h"
#include "../../deps/qsp/bindings/default/qsp_default.h"
#include "../../deps/tinyxml/tinyxml.h"

using namespace std;
//using namespace Awesomium;

namespace QuestNavigator {

	// Константы
	// Перенесено, см. Constants.h
//	static const string DEFAULT_CONTENT_REL_PATH = "standalone_content";
//	static const string ASSETS_DIR = "assets";
//	static const string SKINS_DIR = "skins";
//	static const string QSPLIB_DIR = "qsplib";
//	static const string APP_DATA_DIR = "Quest Navigator Data";
//	static const string GAME_CACHE_DIR = "Cached Games";
//	static const string DEFAULT_SKIN_NAME = "default";
//	static const string DEFAULT_SKIN_FILE = "gameAwesomium.html";
//	static const string DEFAULT_CONFIG_FILE = "config.xml";
//	static const string DEFAULT_SAVE_REL_PATH = "Сохранения игр Quest Navigator";
//	static const string QN_WINDOWS_UPDATE_FEED = "http://feeds.feedburner.com/text-games/quest-navigator-windows";
//	static const string QN_COMPANY_NAME = "QSP";
//	static const string QN_APP_NAME = "Quest Navigator";
//	static const string QN_VERSION = "0.0.29-test";
//	static const string QN_APP_GUID = "95b90169-f70d-4269-b982-d9c3038b8348";
//	static const wchar_t szWindowClass[] = L"QnViewWinClass";
//	static const wchar_t szLogWindowClass[] = L"QnLogWinClass";
//
//	static const string OPTION_ENABLE_SOUND_CACHE = "-enable-sound-cache";
//	static const string OPTION_DEFAULT_SKIN = "-default-skin";
//	static const string OPTION_RESTART = "-restart";
//#ifdef _WIN32
//	static const string PATH_DELIMITER = "\\";
//#else
//	static const string PATH_DELIMITER = "/";
//#endif

	// Тип данных для передачи между экземплярами плеера, а также вспомогательными окнами.
	enum eIpcDataType {
		eidtRestart = 1,
		eidtLog
	};

	// Коды ошибок.
	enum eErrorCodes {
		eecUnableEnterCs1 = 1,			// Не удалось войти в критическую секцию (1).
		eecFailToCreateEvent,			// Не получилось создать событие.
		eecFailToCreateTimer,			// Не получилось создать таймер.
		eecFailToSetEvent,				// Не удалось запустить событие синхронизации потоков.
		eecFailToCloseHandle,			// Не удалось высвободить описатель объекта ядра.
		eecUnableEnterCs2,				// Не удалось войти в критическую секцию (2).
		eecLibThreadAlreadyStarted,		// Не удалось запустить поток библиотеки: он уже запущен.
		eecFailToInitCs,				// Не удалось проинициализировать структуру критической секции.
		eecFailToBeginLibThread,		// Не получилось создать поток интерпретатора.
		eecUnableEnterCs3,				// Не удалось войти в критическую секцию (3).
		eecFailToCalcBorders,			// Не удалось рассчитать толщину рамок окна.
		eecFailToCreateMainWindow		// Не удалось создать основное окно плеера.
	};

	// Прочее

	// Устанавливаем конфигурацию плеера при старте
	// См. ConfigurationBuilder
	//bool initOptions(string contentPath);
	// Загружаем настройки игры из файла config.xml
	bool loadGameConfig();
	// Готовим игру к запуску
	bool prepareGameFiles();
	// Получаем идентификатор для мьютекса.
	string getInstanceMutexId();
	// Выводим текст в консоль.
	void writeConsole(HWND hWnd, string text);

	// Стиль для окна согласно настройкам игры
	DWORD getWindowStyle();
	// Переключение полноэкранного режима
	void toggleFullscreenByHwnd(HWND hWnd);
	// Установка полноэкранного режима.
	void setFullscreenByHwnd(HWND hWnd, bool fullscreen);
}
