#pragma once

#include "EventManager.h"
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"

namespace QuestNavigator
{
	class Library
	{
	public:
		Library();
		~Library();

		void Library::inject(
			EventManager* eventManager
		);

		// Запуск потока библиотеки
		void StartLibThread();
		// Остановка потока библиотеки
		void StopLibThread();

	protected:
		// Для вызова из статики.
		EventManager* getEventManager();

	private:
		EventManager* eventManager;

		HANDLE libThread;

		// Основная функция потока библиотеки
		static unsigned int __stdcall libThreadFunc(void* pvParam);
		
		// Проверка результатов выполнения библиотечного кода
		static void CheckQspResult(QSP_BOOL successfull, string failMsg);

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
	//		static vector<ContainerMenuItem> menuList;
	//		static int timerInterval;
}