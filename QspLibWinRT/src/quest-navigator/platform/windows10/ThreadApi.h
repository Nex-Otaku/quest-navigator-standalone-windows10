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
	};
}
