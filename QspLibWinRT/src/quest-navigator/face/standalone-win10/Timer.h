#pragma once

namespace QuestNavigator
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		// Установка и запуск таймера
		void startTimer();
		// Остановка таймера
		void stopTimer();
		// Создаём таймер.
		HANDLE CreateTimer();

		// Установка интервала срабатывания таймера.
		void setTimerInterval(int msecs);

	private:
		int timerInterval;
	};
}