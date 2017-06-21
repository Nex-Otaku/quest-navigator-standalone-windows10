#include "pch.h"
#include "ThreadManager.h"
#include "..\..\core\dialogs.h"

namespace QuestNavigator {
	ThreadManager::ThreadManager()
	{
	}

	ThreadManager::~ThreadManager()
	{
	}

	void ThreadManager::inject(ThreadApi* threadApi)
	{
		this->threadApi = threadApi;
	}

	// ������� �������
	bool ThreadManager::waitForSingle(HANDLE handle)
	{
		//DWORD res = WaitForSingleObject(handle, INFINITE);
		DWORD res = WaitForSingleObjectEx(handle, INFINITE, FALSE);
		if (res != WAIT_OBJECT_0) {
			showError("waitForSingle: �� ������� ��������� ������� �������������");
			return false;
		}
		return true;
	}

	// ������������ ��������� � �������� ���� ��� �� ���.
	void ThreadManager::freeHandle(HANDLE handle)
	{
		BOOL res = CloseHandle(handle);
		if (res == 0) {
			showError("�� ������� ����������� ��������� ������� ����.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToCloseHandle);
		}
	}

	bool ThreadManager::checkForSingle(HANDLE handle)
	{
		// ���������, �������� �� ������ �������������.
		// ���� ����������, ����� ���������� "false".
		// ��� �������� ������� ������� ������������ "waitForSingle".
		DWORD res = WaitForSingleObjectEx(handle, 0, FALSE);
		showError("ThreadManager::checkForSingle 1");
		if ((res == WAIT_ABANDONED) || (res == WAIT_FAILED)) {
			showError("ThreadManager::checkForSingle sync failure");
			showError("���� �������������");
			return false;
		}
		showError("ThreadManager::checkForSingle 2");
		showError("ThreadManager::checkForSingle: res = " + std::to_string((int)res));
		if (res == WAIT_TIMEOUT) {
			showError("ThreadManager::checkForSingle wait timeout");
		}
		return res == WAIT_OBJECT_0;
	}

	DWORD ThreadManager::waitForMultiple(DWORD nCount, const HANDLE* lpHandles)
	{
		// ������� ����� �� ������� �������������
		// ��� Windows10 ���������� WaitForMultipleObjectsEx ������ WaitForMultipleObjects
		DWORD res = WaitForMultipleObjectsEx(nCount, lpHandles, FALSE, INFINITE, FALSE);
		return res;
	}

	// ������ ������ ���� ��� ������������� �������,
	// ������� � �����������, ������������������ � ������� ���������.
	HANDLE ThreadManager::CreateSyncEvent()
	{
		//HANDLE eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		HANDLE eventHandle = CreateEventEx(NULL, NULL, NULL, NULL);
		if (eventHandle == NULL) {
			showError("�� ���������� ������� ������ ���� \"�������\" ��� ������������� �������.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToCreateEvent);
		}
		return eventHandle;
	}
	
	BOOL ThreadManager::setEvent(HANDLE handle)
	{
		BOOL res = SetEvent(handle);
		if (res == 0) {
			showError("�� ������� ��������� ������� ������������� �������.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToSetEvent);
		}
	}
}