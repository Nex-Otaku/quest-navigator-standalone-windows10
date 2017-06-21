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

	// Ожидаем события
	bool ThreadManager::waitForSingle(HANDLE handle)
	{
		//DWORD res = WaitForSingleObject(handle, INFINITE);
		DWORD res = WaitForSingleObjectEx(handle, INFINITE, FALSE);
		if (res != WAIT_OBJECT_0) {
			showError("waitForSingle: Не удалось дождаться события синхронизации");
			return false;
		}
		return true;
	}

	// Высвобождаем описатель и ругаемся если что не так.
	void ThreadManager::freeHandle(HANDLE handle)
	{
		BOOL res = CloseHandle(handle);
		if (res == 0) {
			showError("Не удалось высвободить описатель объекта ядра.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToCloseHandle);
		}
	}

	bool ThreadManager::checkForSingle(HANDLE handle)
	{
		// Проверяем, доступен ли объект синхронизации.
		// Если недоступен, сразу возвращаем "false".
		// Для ожидания объекта следует использовать "waitForSingle".
		DWORD res = WaitForSingleObjectEx(handle, 0, FALSE);
		showError("ThreadManager::checkForSingle 1");
		if ((res == WAIT_ABANDONED) || (res == WAIT_FAILED)) {
			showError("ThreadManager::checkForSingle sync failure");
			showError("Сбой синхронизации");
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
		// Ожидаем любое из событий синхронизации
		// Для Windows10 используем WaitForMultipleObjectsEx вместо WaitForMultipleObjects
		DWORD res = WaitForMultipleObjectsEx(nCount, lpHandles, FALSE, INFINITE, FALSE);
		return res;
	}

	// Создаём объект ядра для синхронизации потоков,
	// событие с автосбросом, инициализированное в занятом состоянии.
	HANDLE ThreadManager::CreateSyncEvent()
	{
		//HANDLE eventHandle = CreateEvent(NULL, FALSE, FALSE, NULL);
		HANDLE eventHandle = CreateEventEx(NULL, NULL, NULL, NULL);
		if (eventHandle == NULL) {
			showError("Не получилось создать объект ядра \"событие\" для синхронизации потоков.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToCreateEvent);
		}
		return eventHandle;
	}
	
	BOOL ThreadManager::setEvent(HANDLE handle)
	{
		BOOL res = SetEvent(handle);
		if (res == 0) {
			showError("Не удалось запустить событие синхронизации потоков.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToSetEvent);
		}
	}
}