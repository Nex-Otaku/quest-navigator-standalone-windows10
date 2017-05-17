#pragma once

namespace QuestNavigator
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		// ��������� � ������ �������
		void startTimer();
		// ��������� �������
		void stopTimer();
		// ������ ������.
		HANDLE CreateTimer();

		// ��������� ��������� ������������ �������.
		void setTimerInterval(int msecs);

	private:
		int timerInterval;
	};
}