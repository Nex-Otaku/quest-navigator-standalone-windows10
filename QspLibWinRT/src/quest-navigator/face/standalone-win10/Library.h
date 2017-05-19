#pragma once

#include "EventManager.h"
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "Timer.h"

namespace QuestNavigator
{
	class Library
	{
	public:
		Library();
		~Library();

		void Library::inject(
			EventManager* eventManager,
			Timer* timer
		);

		// Запуск потока библиотеки
		void StartLibThread();
		// Остановка потока библиотеки
		void StopLibThread();

		// Проверка результатов выполнения библиотечного кода
		static void CheckQspResult(QSP_BOOL successfull, string failMsg);

	private:
		EventManager* eventManager;
		Timer* timer;

		HANDLE libThread;

		// Основная функция потока библиотеки
		static unsigned int __stdcall libThreadFunc(void* pvParam);
		
		// ********************************************************************
		// Переменные библиотеки
		// ********************************************************************
		
	};
	//		// ********************************************************************
	//		// THREADS
	//		// ********************************************************************
	//
	//		// Запуск потока библиотеки
	//		void StartLibThread();
	//		// Остановка потока библиотеки
	//		void StopLibThread();
	//		// Основная функция потока библиотеки
	//		static unsigned int __stdcall libThreadFunc(void* pvParam);
	//
	//		// Проверка результатов выполнения библиотечного кода
	//		static void CheckQspResult(QSP_BOOL successfull, string failMsg);

	//		// ********************************************************************
	//		// Переменные библиотеки
	//		// ********************************************************************
	//
	//		static QnApplicationListener* listener;
}