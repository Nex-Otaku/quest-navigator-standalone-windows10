#pragma once

/*
Сюда выносим все функции работы с потоками,
которые зависят от используемой платформы.

Управление событиями, создание потока - на Win32 это одни функции, на WinRT другие.

Здесь делаем тонкую обёртку, без особой логики.
Так мы сможем переключиться с одного набора платформенных функций на другие без переписывания остального кода.
*/

namespace QuestNavigator {
	class ThreadApi
	{
	public:
		ThreadApi();
		~ThreadApi();

		// Обёртка для WaitForSingleObject.
		DWORD WINAPI waitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds);

		// Обёртка для CloseHandle.
		BOOL WINAPI closeHandle(HANDLE hObject);

		// Обёртка для WaitForMultipleObjects.
		DWORD WINAPI waitForMultipleObjects(
			DWORD nCount, 
			const HANDLE* lpHandles,
			BOOL bWaitAll,
			DWORD dwMilliseconds
		);

		// Обёртка для CreateEvent.
		HANDLE WINAPI createEvent(
				LPSECURITY_ATTRIBUTES lpEventAttributes,
				BOOL bManualReset,
				BOOL bInitialState,
				LPCWSTR lpName
			);

		// Обёртка для SetEvent.
		BOOL WINAPI setEvent(HANDLE hEvent);

		// Обёртка для CreateThread.
		HANDLE WINAPI createThread(
			LPSECURITY_ATTRIBUTES unusedThreadAttributes, 
			SIZE_T unusedStackSize, 
			LPTHREAD_START_ROUTINE lpStartAddress, 
			LPVOID lpParameter, 
			DWORD dwCreationFlags, 
			LPDWORD unusedThreadId
		);
	};
}
