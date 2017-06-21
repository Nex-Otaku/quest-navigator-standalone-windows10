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
		// Проверка события синхронизации.
		bool checkForSingle(HANDLE handle);
		// Ожидание любого события.
		DWORD waitForMultiple(DWORD nCount, const HANDLE* lpHandles);
		// Создаём объект ядра для синхронизации потоков,
		// событие с автосбросом, инициализированное в занятом состоянии.
		HANDLE CreateSyncEvent();
		// Запуск события.
		BOOL setEvent(HANDLE handle);
	private:
		ThreadApi* threadApi;
	};
}