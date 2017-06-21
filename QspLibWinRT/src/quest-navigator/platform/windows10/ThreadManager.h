#pragma once

#include "ThreadApi.h"

/* ������ ��� ���������� ��������. */

namespace QuestNavigator {
	class ThreadManager
	{
	public:
		ThreadManager();
		~ThreadManager();

		void inject(ThreadApi* threadApi);

		// ��������������� ������� ��� ������������� �������.

		// ������� �������
		bool waitForSingle(HANDLE handle);
		// ������������ ��������� � �������� ���� ��� �� ���.
		void freeHandle(HANDLE handle);
		// �������� ������� �������������.
		bool checkForSingle(HANDLE handle);
		// �������� ������ �������.
		DWORD waitForMultiple(DWORD nCount, const HANDLE* lpHandles);
		// ������ ������ ���� ��� ������������� �������,
		// ������� � �����������, ������������������ � ������� ���������.
		HANDLE CreateSyncEvent();
		// ������ �������.
		BOOL setEvent(HANDLE handle);
	private:
		ThreadApi* threadApi;
	};
}