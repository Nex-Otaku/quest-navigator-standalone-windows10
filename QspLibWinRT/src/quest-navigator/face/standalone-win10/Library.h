#pragma once

#include "EventManager.h"
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "Timer.h"
#include "JsExecutor.h"
#include "..\..\platform\windows10\ThreadManager.h"
#include "SaveFileManager.h"
#include "AudioManager.h"

namespace QuestNavigator
{
	// Объявляем класс, чтобы избежать циклической зависимости.
	// Класс будет определён позже в соответствующем заголовочном файле.
	class SaveFileManager;

	class Library
	{
	public:
		Library();
		~Library();

		void Library::inject(
			EventManager* eventManager,
			Timer* timer,
			JsExecutor* jsExecutor,
			ThreadManager* threadManager,
			SaveFileManager* saveFileManager,
			AudioManager* audioManager
		);

		// ********************************************************************
		// THREADS
		// ********************************************************************

		// Запуск потока библиотеки
		void StartLibThread();
		// Остановка потока библиотеки
		void StopLibThread();

		// Проверка результатов выполнения библиотечного кода
		void CheckQspResult(QSP_BOOL successfull, string failMsg);

	private:
		EventManager* eventManager;
		Timer* timer;
		JsExecutor* jsExecutor;
		ThreadManager* threadManager;
		SaveFileManager* saveFileManager;
		AudioManager* audioManager;

		HANDLE libThread;

		// Основная функция потока библиотеки
		//static unsigned int __stdcall libThreadFunc(void* pvParam);
		//DWORD(WINAPI *PTHREAD_START_ROUTINE)(
		//	LPVOID lpThreadParameter
		//	)
		static DWORD __stdcall libThreadFunc(LPVOID lpParameter);
	};
}