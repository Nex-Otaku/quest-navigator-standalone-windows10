#include "pch.h"
#include "EventManager.h"

namespace QuestNavigator
{

	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}

	void EventManager::executeAction(int pos)
	{
		// Контекст UI


		//		// Контекст UI
		//		if (args.size() < 1) {
		//			showError("Не указан параметр для executeAction!");
		//			return;
		//		}
		//
		//		if (!checkForSingle(evLibIsReady))
		//			return;
		//
		//		JSValue jsPos = args[0];
		//		int pos = jsPos.ToInteger();
		//		lockData();
		//		g_sharedData[evExecuteAction].num = pos;
		//		runSyncEvent(evExecuteAction);
		//		unlockData();
	}

	// Работа с синхронизацией и потоками.

	// Создаём объект ядра для синхронизации потоков,
	// событие с автосбросом, инициализированное в занятом состоянии.
	HANDLE EventManager::CreateSyncEvent()
	{
		//		HANDLE eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		//		if (eventHandle == NULL) {
		//			showError("Не получилось создать объект ядра \"событие\" для синхронизации потоков.");
		//			exit(eecFailToCreateEvent);
		//		}
		//		return eventHandle;
	}

	// Создаём таймер.
	HANDLE EventManager::CreateTimer()
	{
		return HANDLE();
		//		HANDLE timerHandle = CreateWaitableTimer(NULL, FALSE, NULL);
		//		if (timerHandle == NULL) {
		//			showError("Не получилось создать таймер.");
		//			exit(eecFailToCreateTimer);
		//		}
		//		return timerHandle;
	}

	// Получаем HANDLE события по его индексу
	HANDLE EventManager::getEventHandle(eSyncEvent ev)
	{
		return HANDLE();
		//		return g_eventList[ev];
	}

	// Запускаем событие
	void EventManager::runSyncEvent(eSyncEvent ev)
	{
		//		BOOL res = SetEvent(getEventHandle(ev));
		//		if (res == 0) {
		//			showError("Не удалось запустить событие синхронизации потоков.");
		//			exit(eecFailToSetEvent);
		//		}
	}

	// Высвобождаем описатель и ругаемся если что не так.
	void EventManager::freeHandle(HANDLE handle)
	{
		//		BOOL res = CloseHandle(handle);
		//		if (res == 0) {
		//			showError("Не удалось высвободить описатель объекта ядра.");
		//			exit(eecFailToCloseHandle);
		//		}
	}

	// Входим в критическую секцию
	void EventManager::lockData()
	{
		//		try {
		//			EnterCriticalSection(&g_csSharedData);
		//		} catch (...) {
		//			showError("Не удалось войти в критическую секцию.");
		//			exit(eecUnableEnterCs2);
		//		}
	}

	// Выходим из критической секции
	void EventManager::unlockData()
	{
		//		LeaveCriticalSection(&g_csSharedData);
	}

	// Ожидаем события
	bool EventManager::waitForSingle(HANDLE handle)
	{
		return false;
		//		DWORD res = WaitForSingleObject(handle, INFINITE);
		//		if (res != WAIT_OBJECT_0) {
		//			showError("Не удалось дождаться события синхронизации");
		//			return false;
		//		}
		//		return true;
	}

	bool EventManager::waitForSingle(eSyncEvent ev)
	{
		return false;
		//		return waitForSingle(getEventHandle(ev));
	}

	bool EventManager::waitForSingleLib(eSyncEvent ev)
	{
		return false;
		//		// Контекст библиотеки.
		//		// Мы должны иметь возможность в любой момент остановить игру либо поток библиотеки.
		//		// Поэтому при ожидании в библиотеке единичного события синхронизации,
		//		// такого как например закрытие диалога,
		//		// мы вместо "waitForSingle" вызываем "waitForSingleLib".
		//		// Эта функция дополнительно проверяет на наличие события, 
		//		// указывающего, что мы должны остановить игру либо поток библиотеки.
		//
		//		// События для синхронизации потоков
		//		HANDLE eventList[3];
		//		eSyncEvent syncEvents[3];
		//		syncEvents[0] = evShutdown;
		//		syncEvents[1] = evStopGame;
		//		syncEvents[2] = ev;
		//		for (int i = 0; i < 3; i++) {
		//			eventList[i] = getEventHandle(syncEvents[i]);
		//		}
		//
		//		DWORD res = WaitForMultipleObjects((DWORD)3, eventList, FALSE, INFINITE);
		//		if ((res < WAIT_OBJECT_0) || (res > (WAIT_OBJECT_0 + 3 - 1))) {
		//			showError("Не удалось дождаться единичного события синхронизации библиотеки.");
		//		} else {
		//			// Если событие было "evShutdown" или "evStopGame",
		//			// вызываем их заново.
		//			// Это необходимо, так как вызов "WaitForMultipleObjects" их уже сбросил.
		//			for (int i = 0; i < 3; i++) {
		//				if (eventList[i])
		//				break;
		//			}
		//			eSyncEvent breakingEvent = syncEvents[res];
		//			if (breakingEvent != ev) {
		//				runSyncEvent(breakingEvent);
		//			}
		//		}
		//		return true;
	}

	bool EventManager::checkForSingle(eSyncEvent ev)
	{
		return false;
		//		// Проверяем, доступен ли объект синхронизации.
		//		// Если недоступен, сразу возвращаем "false".
		//		// Для ожидания объекта следует использовать "waitForSingle".
		//		HANDLE handle = getEventHandle(ev);
		//		DWORD res = WaitForSingleObject(handle, 0);
		//		if ((res == WAIT_ABANDONED) || (res == WAIT_FAILED)) {
		//			showError("Сбой синхронизации");
		//			return false;
		//		}
		//		return res == WAIT_OBJECT_0;
	}
}