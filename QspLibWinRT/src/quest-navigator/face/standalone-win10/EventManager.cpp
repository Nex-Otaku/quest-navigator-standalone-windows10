#include "pch.h"
#include "EventManager.h"
#include <string>
#include "..\..\core\dialogs.h"
#include "..\..\core\thread_sync.h"
#include "..\..\core\events.h"

using namespace std;

namespace QuestNavigator
{
	EventManager::EventManager()
	{
	}

	EventManager::~EventManager()
	{
	}

	void EventManager::inject(Timer* timer, UwpJsExecutor^ uwpJsExecutor)
	{
		this->timer = timer;

		// �������.
		this->uwpJsExecutor = uwpJsExecutor;
	}

	// ������ ������� �� UI.

	// JsListener

	void EventManager::executeAction(int pos)
	{
		// �������� UI
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
		// �������� UI
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
		// �������� UI
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
		// �������� UI
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
		// �������� UI
		runSyncEvent(evMsgClosed);
	}

	void EventManager::errorClosed()
	{
		// �������� UI
		runSyncEvent(evErrorClosed);
	}

	void EventManager::menuClosed(int pos)
	{
		// �������� UI
		lockData();
		g_sharedData[evMenuClosed].num = pos;
		runSyncEvent(evMenuClosed);
		unlockData();
	}

	void EventManager::inputClosed(string text)
	{
		// �������� UI
		lockData();
		g_sharedData[evInputClosed].str = text;
		runSyncEvent(evInputClosed);
		unlockData();
	}

	void EventManager::mute(bool flag)
	{
		// �������� UI
		lockData();
		g_sharedData[evMute].flag = flag;
		runSyncEvent(evMute);
		unlockData();
	}

	void EventManager::inputStringChanged(string text)
	{
		// �������� UI
		lockData();
		g_sharedData[evInputStringChanged].str = text;
		runSyncEvent(evInputStringChanged);
		unlockData();
	}

	void EventManager::inputStringEntered()
	{
		// �������� UI
		// ������ Enter � ������ �����
		runSyncEvent(evInputStringEntered);
	}

	// App

	void EventManager::runGame(string fileName, int gameIsStandalone)
	{
		this->uwpJsExecutor->jsCallDebug("EventManager::runGame 1");
		// �������� UI
		if (!checkForSingleEvent(evLibIsReady)) {
			return;
		}

		this->uwpJsExecutor->jsCallDebug("EventManager::runGame 2");
		// ������� ������ ��� �������� � �����
		lockData();
		g_sharedData[evRunGame].str = fileName;
		// ������� ��������� �� ������� � ����.
		g_sharedData[evRunGame].num = gameIsStandalone;
		runSyncEvent(evRunGame);
		unlockData();
		this->uwpJsExecutor->jsCallDebug("EventManager::runGame 3");
	}

	void EventManager::stopGame()
	{
		// �������� UI
		// �� ������ ����� ����������� ���������� ���� � ����� ������.
		runSyncEvent(evStopGame);
		waitForSingleEvent(evGameStopped);
	}

	// Library

	void EventManager::initEvents()
	{
		// �������������� ������� �������������.
		// ������������ ������� - ������� � �����������, 
		// ������������������ � ������� ���������, � ���� ������.
		for (int i = 0; i < (int)evLast; i++) {
			HANDLE eventHandle = (i == (int)evTimer) ? this->timer->CreateTimer() : CreateSyncEvent();
			if (eventHandle == NULL)
				return;
			g_eventList[i] = eventHandle;
		}
	}

	void EventManager::initSharedData()
	{
		// �������������� ��������� ����������� ������
		try {
			InitializeCriticalSection(&g_csSharedData);
		}
		catch (...) {
			showError("�� ������� ������������������� ��������� ����������� ������.");

			// STUB
			// ������� ����� �� ����������?
			//exit(eecFailToInitCs);
			return;
		}
	}

	void EventManager::freeEvents()
	{
		// ��������� ������ �������
		for (int i = 0; i < (int)evLast; i++) {
			freeHandle(g_eventList[i]);
			g_eventList[i] = NULL;
		}
	}

	void EventManager::freeSharedData()
	{
		// ������������ ��������� ����������� ������
		DeleteCriticalSection(&g_csSharedData);
	}

	void EventManager::shutdown()
	{
		runSyncEvent(evShutdown);
	}

	void EventManager::libIsReady()
	{
		// �������� ������ UI, ��� ���������� ������ � ���������� ������
		runSyncEvent(evLibIsReady);
	}

	void EventManager::gameStopped()
	{
		// ���������� ��������, ��� ���� �����������.
		runSyncEvent(evGameStopped);
	}

	DWORD EventManager::waitForAnyEvent()
	{
		// ������� ����� �� ������� �������������
		DWORD res = WaitForMultipleObjects((DWORD)evLastUi, g_eventList, FALSE, INFINITE);
		return res;
	}

	bool EventManager::isValidEvent(DWORD waitResult)
	{
		return (waitResult < WAIT_OBJECT_0) || (waitResult >(WAIT_OBJECT_0 + evLast - 1));
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
	// ������ � �������������� � ��������.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// public

	// �������, ���� ����� ���������� �� ����� ����� � ��������� ���������.
	void EventManager::waitForLibIsReady()
	{
		waitForSingleEvent(evLibIsReady);
	}

	// private

	// ������ ������ ���� ��� ������������� �������,
	// ������� � �����������, ������������������ � ������� ���������.
	HANDLE EventManager::CreateSyncEvent()
	{
		HANDLE eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		if (eventHandle == NULL) {
			showError("�� ���������� ������� ������ ���� \"�������\" ��� ������������� �������.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToCreateEvent);
		}
		return eventHandle;
	}

	// �������� HANDLE ������� �� ��� �������
	HANDLE EventManager::getEventHandle(eSyncEvent ev)
	{
		return g_eventList[ev];
	}

	// ��������� �������
	void EventManager::runSyncEvent(eSyncEvent ev)
	{
		BOOL res = SetEvent(getEventHandle(ev));
		if (res == 0) {
			showError("�� ������� ��������� ������� ������������� �������.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToSetEvent);
		}
	}

	// ������ � ����������� ������
	void EventManager::lockData()
	{
		try {
			EnterCriticalSection(&g_csSharedData);
		} catch (...) {
			showError("�� ������� ����� � ����������� ������.");

			// STUB
			// ����� �� ����������?
			//exit(eecUnableEnterCs2);
		}
	}

	// ������� �� ����������� ������
	void EventManager::unlockData()
	{
		LeaveCriticalSection(&g_csSharedData);
	}

	bool EventManager::waitForSingleEvent(eSyncEvent ev)
	{
		return waitForSingle(getEventHandle(ev));
	}

	bool EventManager::waitForSingleLib(eSyncEvent ev)
	{
		// �������� ����������.
		// �� ������ ����� ����������� � ����� ������ ���������� ���� ���� ����� ����������.
		// ������� ��� �������� � ���������� ���������� ������� �������������,
		// ������ ��� �������� �������� �������,
		// �� ������ "waitForSingleEvent" �������� "waitForSingleLib".
		// ��� ������� ������������� ��������� �� ������� �������, 
		// ������������, ��� �� ������ ���������� ���� ���� ����� ����������.
		
		// ������� ��� ������������� �������
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
			showError("�� ������� ��������� ���������� ������� ������������� ����������.");
		} else {
			// ���� ������� ���� "evShutdown" ��� "evStopGame",
			// �������� �� ������.
			// ��� ����������, ��� ��� ����� "WaitForMultipleObjects" �� ��� �������.
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
		// ���������, �������� �� ������ �������������.
		// ���� ����������, ����� ���������� "false".
		// ��� �������� ������� ������� ������������ "waitForSingle".
		this->uwpJsExecutor->jsCallDebug("EventManager::checkForSingleEvent 1");
		HANDLE handle = getEventHandle(ev);
		this->uwpJsExecutor->jsCallDebug("EventManager::checkForSingleEvent 2");
		DWORD res = WaitForSingleObject(handle, 0);
		this->uwpJsExecutor->jsCallDebug("EventManager::checkForSingleEvent 3");
		if ((res == WAIT_ABANDONED) || (res == WAIT_FAILED)) {
			this->uwpJsExecutor->jsCallDebug("EventManager::checkForSingleEvent ���� �������������");
			showError("���� �������������");
			return false;
		}
		this->uwpJsExecutor->jsCallDebug("EventManager::checkForSingleEvent 4");
		return res == WAIT_OBJECT_0;
	}
}