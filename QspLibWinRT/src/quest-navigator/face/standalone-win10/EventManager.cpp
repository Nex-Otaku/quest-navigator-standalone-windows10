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

	// ������ ������� �� UI.

	// JsListener

	void EventManager::executeAction(int pos)
	{
		// �������� UI
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
		// �������� UI
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
		// �������� UI
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
		// �������� UI
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
		if (!checkForSingle(evLibIsReady)) {
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
		waitForSingle(evGameStopped);
	}

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ������ � �������������� � ��������.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// public

	// �������, ���� ����� ���������� �� ����� ����� � ��������� ���������.
	void EventManager::waitForLibIsReady()
	{
		waitForSingle(evLibIsReady);
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

	// ������������ ��������� � �������� ���� ��� �� ���.
	void EventManager::freeHandle(HANDLE handle)
	{
		BOOL res = CloseHandle(handle);
		if (res == 0) {
			showError("�� ������� ����������� ��������� ������� ����.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToCloseHandle);
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

	// ������� �������
	bool EventManager::waitForSingle(HANDLE handle)
	{
		DWORD res = WaitForSingleObject(handle, INFINITE);
		if (res != WAIT_OBJECT_0) {
			showError("�� ������� ��������� ������� �������������");
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
		// �������� ����������.
		// �� ������ ����� ����������� � ����� ������ ���������� ���� ���� ����� ����������.
		// ������� ��� �������� � ���������� ���������� ������� �������������,
		// ������ ��� �������� �������� �������,
		// �� ������ "waitForSingle" �������� "waitForSingleLib".
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

	bool EventManager::checkForSingle(eSyncEvent ev)
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