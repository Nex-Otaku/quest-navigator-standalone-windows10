#pragma once

#include <string>
#include "Timer.h"

using namespace std;

namespace QuestNavigator
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		void inject(
			Timer* timer
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

		// Работа с потоками и синхронизацией.
		
		// Ожидаем, пока поток библиотеки не будет готов к получению сообщений.
		void waitForLibIsReady();

	private:
		Timer* timer;

		// Переменные для работы с потоками

		// Структура для критических секций
		CRITICAL_SECTION g_csSharedData;

		// Разделяемые данные
		struct SharedData
		{
			string str;
			int num;
			//JSValue jsValue; Данные для передачи вызова из библиотеки (из кода игры) в яваскрипт.
			bool flag;
		};
		SharedData g_sharedData[evLast];

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
	};
}
