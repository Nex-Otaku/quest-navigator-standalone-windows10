#include "pch.h"
#include "Timer.h"

namespace QuestNavigator
{
	Timer::Timer()
	{
	}

	Timer::~Timer()
	{
	}

	// Этот вид таймера работает только для десктопных приложений под Windows32, 
	// то есть для Awesomium.
	// Для универсальных приложений Windows10 придётся действовать вот так:
	// http://stackoverflow.com/a/10777772/534651
	// либо вообще отказаться от использования COUNTER.

	// Установка и запуск таймера
	void Timer::startTimer()
	{
		//		// Устанавливаем период выполнения
		//		__int64         qwDueTime;
		//		LARGE_INTEGER   liDueTime;
		//		// Отрицательное 64-битное число указывает, 
		//		// через сколько наносекунд должен сработать первый вызов таймера.
		//		qwDueTime = -(timerInterval * 10000);
		//		liDueTime.LowPart  = (DWORD) ( qwDueTime & 0xFFFFFFFF );
		//		liDueTime.HighPart = (LONG)  ( qwDueTime >> 32 );
		//
		//		//Запускаем таймер
		//		BOOL res = SetWaitableTimer(getEventHandle(evTimer), &liDueTime, (LONG)timerInterval, NULL, NULL, FALSE);
		//		if (res == 0) {
		//			showError("Не удалось установить интервал таймера!");
		//		}
	}

	// Остановка таймера
	void Timer::stopTimer()
	{
		//		BOOL res = CancelWaitableTimer(getEventHandle(evTimer));
		//		if (res == 0) {
		//			showError("Не удалось остановить таймер!");
		//		}
	}
}