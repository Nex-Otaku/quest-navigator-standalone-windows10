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
	bool waitForSingle(HANDLE handle)
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
	void freeHandle(HANDLE handle)
	{
		BOOL res = CloseHandle(handle);
		if (res == 0) {
			showError("�� ������� ����������� ��������� ������� ����.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToCloseHandle);
		}
	}
}