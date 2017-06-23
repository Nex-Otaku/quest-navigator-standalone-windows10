#include "pch.h"
#include "EventManager.h"
#include <string>
#include "..\..\core\dialogs.h"
#include "..\..\core\thread_sync.h"
#include "..\..\core\events.h"
#include "..\..\platform\windows10\ThreadManager.h"

using namespace std;

namespace QuestNavigator
{
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}

	void EventManager::inject(
		Timer* timer,
		UwpJsExecutor^ uwpJsExecutor,
		StringConverter* stringConverter,
		ThreadManager* threadManager
	)
	{
		this->timer = timer;

		// Отладка.
		this->uwpJsExecutor = uwpJsExecutor;
		this->stringConverter = stringConverter;

		this->threadManager = threadManager;
	}

	// Вызовы событий из UI.

	// JsListener

	void EventManager::executeAction(int pos)
	{
		// Контекст UI
		if (!checkForSingleEvent(evLibIsReady)) {
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
		if (!checkForSingleEvent(evLibIsReady)) {
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
		if (!checkForSingleEvent(evLibIsReady)) {
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
		if (!checkForSingleEvent(evLibIsReady)) {
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

	void EventManager::runGame(string fileName, int gameIsStandalone, bool gameIsRunning)
	{
		//callDebug("EventManager::runGame 1");
		// Контекст UI

		// Проверяем состояние библиотеки.
		// Если первый запуск, то ждём, пока библиотека запустится.
		// Если игра уже запущена, то библиотека должна быть уже в готовом состоянии.
		if (gameIsRunning) {
			if (!checkForSingleEvent(evLibIsReady)) {
				callDebug("EventManager::runGame не удалось запустить игру, библиотека не готова");
				return;
			}
		} else {
			waitForSingleEvent(evLibIsReady);
		}

		//callDebug("EventManager::runGame 2");
		// Готовим данные для передачи в поток
		lockData();
		g_sharedData[evRunGame].str = fileName;
		// Передаём настройку из конфига в скин.
		g_sharedData[evRunGame].num = gameIsStandalone;
		runSyncEvent(evRunGame);
		unlockData();
		//callDebug("EventManager::runGame 3");
	}

	void EventManager::stopGame()
	{
		// Контекст UI
		// Мы должны иметь возможность остановить игру в любой момент.
		runSyncEvent(evStopGame);
		waitForSingleEvent(evGameStopped);
	}

	// Library

	void EventManager::initEvents()
	{
		// Инициализируем объекты синхронизации.
		// Используемые объекты - события с автосбросом, 
		// инициализированные в занятом состоянии, и один таймер.
		for (int i = 0; i < (int)evLast; i++) {
			HANDLE eventHandle = /* таймер временно отключен,
								 заполняем описатель как для обычного события.
								 (i == (int)evTimer) ? this->timer->CreateTimer() : */
				threadManager->CreateSyncEvent();
			if (eventHandle == NULL) {
				callDebug("EventManager::initEvents не удалось зарегистрировать событие");
				return;
			}
			g_eventList[i] = eventHandle;
		}
	}

	void EventManager::initSharedData()
	{
		// Инициализируем структуру критической секции
		try {
			InitializeCriticalSection(&g_csSharedData);
		}
		catch (...) {
			showError("Не удалось проинициализировать структуру критической секции.");

			// STUB
			// Сделать выход из приложения?
			//exit(eecFailToInitCs);
			return;
		}
	}

	void EventManager::freeEvents()
	{
		// Закрываем хэндлы событий
		for (int i = 0; i < (int)evLast; i++) {
			threadManager->freeHandle(g_eventList[i]);
			g_eventList[i] = NULL;
		}
	}

	void EventManager::freeSharedData()
	{
		// Высвобождаем структуру критической секции
		DeleteCriticalSection(&g_csSharedData);
	}

	void EventManager::shutdown()
	{
		runSyncEvent(evShutdown);
	}

	bool EventManager::setLibIsReady()
	{
		// Сообщаем потоку UI, что библиотека готова к выполнению команд
		//callDebug("EventManager::libIsReady");
		return runSyncEvent(evLibIsReady);
	}

	void EventManager::gameStopped()
	{
		// Библиотека сообщила, что игра остановлена.
		runSyncEvent(evGameStopped);
	}

	DWORD EventManager::waitForAnyEvent()
	{
		// Ожидаем любое из событий синхронизации
		return threadManager->waitForMultiple((DWORD)evLastUi, g_eventList);
	}

	bool EventManager::isValidEvent(DWORD waitResult)
	{
		return (waitResult >= WAIT_OBJECT_0) && (waitResult < (WAIT_OBJECT_0 + evLast));
	}

	SharedDataDto EventManager::getSharedData(eSyncEvent ev)
	{
		SharedDataDto dto;
		lockData();
		dto.str = g_sharedData[ev].str;
		dto.num = g_sharedData[ev].num;
		dto.flag = g_sharedData[ev].flag;
		unlockData();
		return dto;
	}

	// LibraryListener

	void EventManager::waitForMsgClosed()
	{
		waitForSingleLib(evMsgClosed);
	}

	void EventManager::waitForInputClosed()
	{
		waitForSingleLib(evInputClosed);
	}

	void EventManager::waitForMenuClosed()
	{
		waitForSingleLib(evMenuClosed);
	}

	void EventManager::waitForErrorClosed()
	{
		waitForSingleLib(evErrorClosed);
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Работа с синхронизацией и потоками.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// private

	// Получаем HANDLE события по его индексу
	HANDLE EventManager::getEventHandle(eSyncEvent ev)
	{
		return g_eventList[ev];
	}

	// Запускаем событие
	bool EventManager::runSyncEvent(eSyncEvent ev)
	{
		HANDLE eventHandle = getEventHandle(ev);
		BOOL res = threadManager->setEvent(eventHandle);
		if (res == FALSE) {
			showError("EventManager::runSyncEvent Не удалось запустить событие синхронизации потоков");
		}
		return res == TRUE;
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

	bool EventManager::waitForSingleEvent(eSyncEvent ev)
	{
		return threadManager->waitForSingle(getEventHandle(ev));
	}

	bool EventManager::waitForSingleLib(eSyncEvent ev)
	{
		// Контекст библиотеки.
		// Мы должны иметь возможность в любой момент остановить игру либо поток библиотеки.
		// Поэтому при ожидании в библиотеке единичного события синхронизации,
		// такого как например закрытие диалога,
		// мы вместо "waitForSingleEvent" вызываем "waitForSingleLib".
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
		
		//DWORD res = WaitForMultipleObjects((DWORD)3, eventList, FALSE, INFINITE, FALSE);
		DWORD res = threadManager->waitForMultiple((DWORD)3, eventList);
		if ((res < WAIT_OBJECT_0) || (res > (WAIT_OBJECT_0 + 3 - 1))) {
			showError("EventManager::waitForSingleLib: Не удалось дождаться единичного события синхронизации библиотеки.");
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

	bool EventManager::checkForSingleEvent(eSyncEvent ev)
	{
		//callDebug("EventManager::checkForSingleEvent 1");
		HANDLE handle = getEventHandle(ev);
		//callDebug("EventManager::checkForSingleEvent 2");

		// Проверка события синхронизации.
		return threadManager->checkForSingle(handle);
	}

	void EventManager::callDebug(string message)
	{
		this->uwpJsExecutor->jsCallDebug(stringConverter->convertStdToUwp(message));
	}
}