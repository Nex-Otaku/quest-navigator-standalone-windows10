#pragma once

#include <string>
#include "Timer.h"
#include "..\..\core\events.h"
#include "..\..\core\dto\SharedDataDto.h"

// Отладка.
#include "..\..\platform\windows10\UwpJsExecutor.h"
#include "..\..\platform\windows10\StringConverter.h"

using namespace std;
// Отладка.
using namespace QspLibWinRT;

namespace QuestNavigator
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		void inject(
			Timer* timer,

			// Для отладки.
			UwpJsExecutor^ uwpJsExecutor,
			StringConverter* stringConverter
		);

		// JsListener
		void executeAction(int pos);
		void selectObject(int pos);
		void loadSlotSelected(int index);
		void saveSlotSelected(int index);
		void msgClosed();
		void errorClosed();
		void menuClosed(int pos);
		void inputClosed(string text);
		void mute(bool flag);
		void inputStringChanged(string text);
		void inputStringEntered();

		// App
		void runGame(string fileName, int gameIsStandalone);
		void stopGame();

		// Library
		void initEvents();
		void initSharedData();
		void freeEvents();
		void freeSharedData();

		void shutdown();
		void libIsReady();
		void gameStopped();

		DWORD waitForAnyEvent();
		bool isValidEvent(DWORD waitResult);
		SharedDataDto getSharedData(eSyncEvent ev);

		// LibraryListener
		void waitForMsgClosed();
		void waitForInputClosed();
		void waitForMenuClosed();
		void waitForErrorClosed();

		// Работа с потоками и синхронизацией.
		
		// Ожидаем, пока поток библиотеки не будет готов к получению сообщений.
		void waitForLibIsReady();

	private:
		// Отладка.
		UwpJsExecutor^ uwpJsExecutor;
		StringConverter* stringConverter;

		Timer* timer;

		// Переменные для работы с потоками

		// Структура для критических секций
		CRITICAL_SECTION g_csSharedData;

		// Разделяемые данные
		SharedDataDto g_sharedData[evLast];

		// События для синхронизации потоков
		HANDLE g_eventList[evLast];

		// Создаём объект ядра для синхронизации потоков,
		// событие с автосбросом, инициализированное в занятом состоянии.
		HANDLE CreateSyncEvent();
		// Получаем HANDLE события по его индексу
		HANDLE getEventHandle(eSyncEvent ev);
		// Запускаем событие
		void runSyncEvent(eSyncEvent ev);
		// Входим в критическую секцию
		void lockData();
		// Выходим из критической секции
		void unlockData();
		// Ожидаем события
		bool waitForSingleEvent(eSyncEvent ev);
		bool waitForSingleLib(eSyncEvent ev);
		bool checkForSingleEvent(eSyncEvent ev);

		// Отладка.
		void callDebug(string message);
	};
}
