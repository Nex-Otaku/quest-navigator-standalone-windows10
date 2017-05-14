#pragma once

namespace QuestNavigator
{
	class Library
	{
	public:
		Library();
		~Library();

		// Запуск потока библиотеки
		void StartLibThread();
		// Остановка потока библиотеки
		void StopLibThread();
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
}