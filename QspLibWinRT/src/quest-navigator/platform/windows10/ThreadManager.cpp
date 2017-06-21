#include "pch.h"
#include "ThreadManager.h"
#include "..\..\core\dialogs.h"
#include "ThreadApi.h"

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
		DWORD res = threadApi->waitForSingleObject(handle, INFINITE);
		if (res != WAIT_OBJECT_0) {
			showError("ThreadManager::waitForSingle: Не удалось дождаться события синхронизации");
			return false;
		}
		return true;
	}

	// Высвобождаем описатель и ругаемся если что не так.
	void ThreadManager::freeHandle(HANDLE handle)
	{
		BOOL res = threadApi->closeHandle(handle);
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
		DWORD res = threadApi->waitForSingleObject(handle, 0);
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
		DWORD res = threadApi->waitForMultipleObjects(nCount, lpHandles, FALSE, INFINITE);
		return res;
	}

	// Создаём объект ядра для синхронизации потоков,
	// событие с автосбросом, инициализированное в занятом состоянии.
	HANDLE ThreadManager::CreateSyncEvent()
	{
		HANDLE eventHandle = threadApi->createEvent(NULL, FALSE, FALSE, NULL);
		if (eventHandle == NULL) {
			showError("ThreadManager::CreateSyncEvent Не получилось создать объект ядра \"событие\" для синхронизации потоков.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToCreateEvent);
		}
		return eventHandle;
	}
	
	BOOL ThreadManager::setEvent(HANDLE handle)
	{
		BOOL res = threadApi->setEvent(handle);
		if (res == 0) {
			DWORD error = GetLastError();


			showError("ThreadManager::setEvent Не удалось запустить событие синхронизации потоков.");
			showError("ThreadManager::setEvent Код ошибки: " + std::to_string((int)error));

			// STUB
			// Выход из приложения?
			//exit(eecFailToSetEvent);
		}
		return res;
	}

	HANDLE ThreadManager::CreateThread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter)
	{
		HANDLE threadHandle = (HANDLE)threadApi->createThread(NULL, 0, lpStartAddress, lpParameter, 0, NULL);
		return threadHandle;
	}
}