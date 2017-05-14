#include "pch.h"
#include "EventManager.h"
#include <string>
#include "..\..\core\dialogs.h"

using namespace std;

namespace QuestNavigator
{
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}

	// Вызовы событий из UI.

	// JsListener

	void EventManager::executeAction(int pos)
	{
		// Контекст UI
		if (!checkForSingle(evLibIsReady)) {
			return;
		}
		
		lockData();
		g_sharedData[evExecuteAction].num = pos;
		runSyncEvent(evExecuteAction);
		unlockData();
	}

	void EventManager::selectObject(int pos)
	{
		// Контекст UI
		if (!checkForSingle(evLibIsReady)) {
			return;
		}
		
		lockData();
		g_sharedData[evSelectObject].num = pos;
		runSyncEvent(evSelectObject);
		unlockData();
	}

	void EventManager::loadSlotSelected(int index)
	{
		// Контекст UI
		if (!checkForSingle(evLibIsReady)) {
			return;
		}

		lockData();
		g_sharedData[evLoadSlotSelected].num = index;
		runSyncEvent(evLoadSlotSelected);
		unlockData();
	}

	void EventManager::saveSlotSelected(int index)
	{
		// Контекст UI
		if (!checkForSingle(evLibIsReady)) {
			return;
		}

		lockData();
		g_sharedData[evSaveSlotSelected].num = index;
		runSyncEvent(evSaveSlotSelected);
		unlockData();
	}

	void EventManager::msgClosed()
	{
		// Контекст UI
		runSyncEvent(evMsgClosed);
	}

	void EventManager::errorClosed()
	{
		// Контекст UI
		runSyncEvent(evErrorClosed);
	}

	void EventManager::menuClosed(int pos)
	{
		// Контекст UI
		lockData();
		g_sharedData[evMenuClosed].num = pos;
		runSyncEvent(evMenuClosed);
		unlockData();
	}

	void EventManager::inputClosed(string text)
	{
		// Контекст UI
		lockData();
		g_sharedData[evInputClosed].str = text;
		runSyncEvent(evInputClosed);
		unlockData();
	}

	void EventManager::mute(bool flag)
	{
		// Контекст UI
		lockData();
		g_sharedData[evMute].flag = flag;
		runSyncEvent(evMute);
		unlockData();
	}

	void EventManager::inputStringChanged(string text)
	{
		// Контекст UI
		lockData();
		g_sharedData[evInputStringChanged].str = text;
		runSyncEvent(evInputStringChanged);
		unlockData();
	}

	void EventManager::inputStringEntered()
	{
		// Контекст UI
		// Нажали Enter в строке ввода
		runSyncEvent(evInputStringEntered);
	}

	// App

	void EventManager::runGame(string fileName, int gameIsStandalone)
	{
		// Контекст UI
		if (!checkForSingle(evLibIsReady)) {
			return;
		}

		// Готовим данные для передачи в поток
		lockData();
		g_sharedData[evRunGame].str = fileName;
		// Передаём настройку из конфига в скин.
		g_sharedData[evRunGame].num = gameIsStandalone;
		runSyncEvent(evRunGame);
		unlockData();
	}

	void EventManager::stopGame()
	{
		// Контекст UI
		// Мы должны иметь возможность остановить игру в любой момент.
		runSyncEvent(evStopGame);
		waitForSingle(evGameStopped);
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Работа с синхронизацией и потоками.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// public

	// Ожидаем, пока поток библиотеки не будет готов к получению сообщений.
	void EventManager::waitForLibIsReady()
	{
		waitForSingle(evLibIsReady);
	}

	// private

	// Создаём объект ядра для синхронизации потоков,
	// событие с автосбросом, инициализированное в занятом состоянии.
	HANDLE EventManager::CreateSyncEvent()
	{
		HANDLE eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (eventHandle == NULL) {
			showError("Не получилось создать объект ядра \"событие\" для синхронизации потоков.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToCreateEvent);
		}
		return eventHandle;
	}

	// Получаем HANDLE события по его индексу
	HANDLE EventManager::getEventHandle(eSyncEvent ev)
	{
		return g_eventList[ev];
	}

	// Запускаем событие
	void EventManager::runSyncEvent(eSyncEvent ev)
	{
		BOOL res = SetEvent(getEventHandle(ev));
		if (res == 0) {
			showError("Не удалось запустить событие синхронизации потоков.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToSetEvent);
		}
	}

	// Высвобождаем описатель и ругаемся если что не так.
	void EventManager::freeHandle(HANDLE handle)
	{
		BOOL res = CloseHandle(handle);
		if (res == 0) {
			showError("Не удалось высвободить описатель объекта ядра.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToCloseHandle);
		}
	}

	// Входим в критическую секцию
	void EventManager::lockData()
	{
		try {
			EnterCriticalSection(&g_csSharedData);
		} catch (...) {
			showError("Не удалось войти в критическую секцию.");

			// STUB
			// Выход из приложения?
			//exit(eecUnableEnterCs2);
		}
	}

	// Выходим из критической секции
	void EventManager::unlockData()
	{
		LeaveCriticalSection(&g_csSharedData);
	}

	// Ожидаем события
	bool EventManager::waitForSingle(HANDLE handle)
	{
		DWORD res = WaitForSingleObject(handle, INFINITE);
		if (res != WAIT_OBJECT_0) {
			showError("Не удалось дождаться события синхронизации");
			return false;
		}
		return true;
	}

	bool EventManager::waitForSingle(eSyncEvent ev)
	{
		return waitForSingle(getEventHandle(ev));
	}

	bool EventManager::waitForSingleLib(eSyncEvent ev)
	{
		// Контекст библиотеки.
		// Мы должны иметь возможность в любой момент остановить игру либо поток библиотеки.
		// Поэтому при ожидании в библиотеке единичного события синхронизации,
		// такого как например закрытие диалога,
		// мы вместо "waitForSingle" вызываем "waitForSingleLib".
		// Эта функция дополнительно проверяет на наличие события, 
		// указывающего, что мы должны остановить игру либо поток библиотеки.
		
		// События для синхронизации потоков
		HANDLE eventList[3];
		eSyncEvent syncEvents[3];
		syncEvents[0] = evShutdown;
		syncEvents[1] = evStopGame;
		syncEvents[2] = ev;
		for (int i = 0; i < 3; i++) {
			eventList[i] = getEventHandle(syncEvents[i]);
		}
		
		DWORD res = WaitForMultipleObjects((DWORD)3, eventList, FALSE, INFINITE);
		if ((res < WAIT_OBJECT_0) || (res > (WAIT_OBJECT_0 + 3 - 1))) {
			showError("Не удалось дождаться единичного события синхронизации библиотеки.");
		} else {
			// Если событие было "evShutdown" или "evStopGame",
			// вызываем их заново.
			// Это необходимо, так как вызов "WaitForMultipleObjects" их уже сбросил.
			for (int i = 0; i < 3; i++) {
				if (eventList[i])
				break;
			}
			eSyncEvent breakingEvent = syncEvents[res];
			if (breakingEvent != ev) {
				runSyncEvent(breakingEvent);
			}
		}
		return true;
	}

	bool EventManager::checkForSingle(eSyncEvent ev)
	{
		// Проверяем, доступен ли объект синхронизации.
		// Если недоступен, сразу возвращаем "false".
		// Для ожидания объекта следует использовать "waitForSingle".
		HANDLE handle = getEventHandle(ev);
		DWORD res = WaitForSingleObject(handle, 0);
		if ((res == WAIT_ABANDONED) || (res == WAIT_FAILED)) {
			showError("Сбой синхронизации");
			return false;
		}
		return res == WAIT_OBJECT_0;
	}
}