#pragma once

#include "ThreadApi.h"

/* Объект для управления потоками. */

namespace QuestNavigator {
	class ThreadManager
	{
	public:
		ThreadManager();
		~ThreadManager();

		void inject(ThreadApi* threadApi);

		// Вспомогательные функции для синхронизации потоков.

		// Ожидаем события
		bool waitForSingle(HANDLE handle);
		// Высвобождаем описатель и ругаемся если что не так.
		void freeHandle(HANDLE handle);

	private:
		ThreadApi* threadApi;
	};
}