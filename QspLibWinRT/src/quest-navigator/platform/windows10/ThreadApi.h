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

		//WaitForSingleObject
		//CloseHandle
		//SetEvent
		//CreateThread
		//CreateEvent
		//WaitForMultipleObjects

		// Обёртка для CreateThread
		HANDLE WINAPI createThread(_In_opt_ LPSECURITY_ATTRIBUTES unusedThreadAttributes, _In_ SIZE_T unusedStackSize, _In_ LPTHREAD_START_ROUTINE lpStartAddress, _In_opt_ LPVOID lpParameter, _In_ DWORD dwCreationFlags, _Out_opt_ LPDWORD unusedThreadId);
	};
}
