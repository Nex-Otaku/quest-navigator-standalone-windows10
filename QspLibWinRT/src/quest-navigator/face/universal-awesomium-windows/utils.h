#pragma once

#include <string>
#include <vector>
#include <Windows.h>
//#include <Awesomium/WebString.h>
#include "../../../deps/qsp/qsp.h"
#include "../../../deps/qsp/bindings/default/qsp_default.h"
#include "../../../deps/tinyxml/tinyxml.h"

using namespace std;
//using namespace Awesomium;

namespace QuestNavigator {

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
	// См. ConfigurationBuilder
	//bool loadGameConfig();

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
