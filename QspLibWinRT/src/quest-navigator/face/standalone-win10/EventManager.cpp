#include "pch.h"
#include "EventManager.h"
#include <string>

using namespace std;

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

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// ������ � �������������� � ��������.
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// ���������� ���������� ��� ������ � ��������
	
	// ��������� ��� ����������� ������
	CRITICAL_SECTION g_csSharedData;
	
	// ����������� ������
	struct SharedData
	{
		string str;
		int num;
		//JSValue jsValue; ������ ��� �������� ������ �� ���������� (�� ���� ����) � ���������.
		bool flag;
	};
	SharedData g_sharedData[evLast];
	
	// ������� ��� ������������� �������
	HANDLE g_eventList[evLast];

	// ������ ������ ���� ��� ������������� �������,
	// ������� � �����������, ������������������ � ������� ���������.
	HANDLE EventManager::CreateSyncEvent()
	{
		//		HANDLE eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		//		if (eventHandle == NULL) {
		//			showError("�� ���������� ������� ������ ���� \"�������\" ��� ������������� �������.");
		//			exit(eecFailToCreateEvent);
		//		}
		//		return eventHandle;
	}

	// ������ ������.
	HANDLE EventManager::CreateTimer()
	{
		return HANDLE();
		//		HANDLE timerHandle = CreateWaitableTimer(NULL, FALSE, NULL);
		//		if (timerHandle == NULL) {
		//			showError("�� ���������� ������� ������.");
		//			exit(eecFailToCreateTimer);
		//		}
		//		return timerHandle;
	}

	// �������� HANDLE ������� �� ��� �������
	HANDLE EventManager::getEventHandle(eSyncEvent ev)
	{
		return HANDLE();
		//		return g_eventList[ev];
	}

	// ��������� �������
	void EventManager::runSyncEvent(eSyncEvent ev)
	{
		//		BOOL res = SetEvent(getEventHandle(ev));
		//		if (res == 0) {
		//			showError("�� ������� ��������� ������� ������������� �������.");
		//			exit(eecFailToSetEvent);
		//		}
	}

	// ������������ ��������� � �������� ���� ��� �� ���.
	void EventManager::freeHandle(HANDLE handle)
	{
		//		BOOL res = CloseHandle(handle);
		//		if (res == 0) {
		//			showError("�� ������� ����������� ��������� ������� ����.");
		//			exit(eecFailToCloseHandle);
		//		}
	}

	// ������ � ����������� ������
	void EventManager::lockData()
	{
		//		try {
		//			EnterCriticalSection(&g_csSharedData);
		//		} catch (...) {
		//			showError("�� ������� ����� � ����������� ������.");
		//			exit(eecUnableEnterCs2);
		//		}
	}

	// ������� �� ����������� ������
	void EventManager::unlockData()
	{
		//		LeaveCriticalSection(&g_csSharedData);
	}

	// ������� �������
	bool EventManager::waitForSingle(HANDLE handle)
	{
		return false;
		//		DWORD res = WaitForSingleObject(handle, INFINITE);
		//		if (res != WAIT_OBJECT_0) {
		//			showError("�� ������� ��������� ������� �������������");
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
		//		// �������� ����������.
		//		// �� ������ ����� ����������� � ����� ������ ���������� ���� ���� ����� ����������.
		//		// ������� ��� �������� � ���������� ���������� ������� �������������,
		//		// ������ ��� �������� �������� �������,
		//		// �� ������ "waitForSingle" �������� "waitForSingleLib".
		//		// ��� ������� ������������� ��������� �� ������� �������, 
		//		// ������������, ��� �� ������ ���������� ���� ���� ����� ����������.
		//
		//		// ������� ��� ������������� �������
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
		//			showError("�� ������� ��������� ���������� ������� ������������� ����������.");
		//		} else {
		//			// ���� ������� ���� "evShutdown" ��� "evStopGame",
		//			// �������� �� ������.
		//			// ��� ����������, ��� ��� ����� "WaitForMultipleObjects" �� ��� �������.
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
		//		// ���������, �������� �� ������ �������������.
		//		// ���� ����������, ����� ���������� "false".
		//		// ��� �������� ������� ������� ������������ "waitForSingle".
		//		HANDLE handle = getEventHandle(ev);
		//		DWORD res = WaitForSingleObject(handle, 0);
		//		if ((res == WAIT_ABANDONED) || (res == WAIT_FAILED)) {
		//			showError("���� �������������");
		//			return false;
		//		}
		//		return res == WAIT_OBJECT_0;
	}
}