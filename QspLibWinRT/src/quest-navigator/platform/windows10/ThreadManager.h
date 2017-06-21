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

	private:
		ThreadApi* threadApi;
	};
}