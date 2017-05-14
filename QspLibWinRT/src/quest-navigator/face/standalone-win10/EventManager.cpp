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

	void EventManager::inject(Timer* timer)
	{
		this->timer = timer;
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
		// �������� UI
		if (!checkForSingleEvent(evLibIsReady)) {
			return;
		}

		// ������� ������ ��� �������� � �����
		lockData();
		g_sharedData[evRunGame].str = fileName;
		// ������� ��������� �� ������� � ����.
		g_sharedData[evRunGame].num = gameIsStandalone;
		runSyncEvent(evRunGame);
		unlockData();
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
		HANDLE handle = getEventHandle(ev);
		DWORD res = WaitForSingleObject(handle, 0);
		if ((res == WAIT_ABANDONED) || (res == WAIT_FAILED)) {
			showError("���� �������������");
			return false;
		}
		return res == WAIT_OBJECT_0;
	}
}