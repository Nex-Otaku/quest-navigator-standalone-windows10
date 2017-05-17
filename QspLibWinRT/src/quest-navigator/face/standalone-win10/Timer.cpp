#include "pch.h"
#include "Timer.h"

namespace QuestNavigator
{
	Timer::Timer()
		: timerInterval(0)
	{
	}

	Timer::~Timer()
	{
	}

	// ���� ��� ������� �������� ������ ��� ���������� ���������� ��� Windows32, 
	// �� ���� ��� Awesomium.
	// ��� ������������� ���������� Windows10 ������� ����������� ��� ���:
	// http://stackoverflow.com/a/10777772/534651
	// ���� ������ ���������� �� ������������� COUNTER.

	// ��������� � ������ �������
	void Timer::startTimer()
	{
		//		// ������������� ������ ����������
		//		__int64         qwDueTime;
		//		LARGE_INTEGER   liDueTime;
		//		// ������������� 64-������ ����� ���������, 
		//		// ����� ������� ���������� ������ ��������� ������ ����� �������.
		//		qwDueTime = -(timerInterval * 10000);
		//		liDueTime.LowPart  = (DWORD) ( qwDueTime & 0xFFFFFFFF );
		//		liDueTime.HighPart = (LONG)  ( qwDueTime >> 32 );
		//
		//		//��������� ������
		//		BOOL res = SetWaitableTimer(getEventHandle(evTimer), &liDueTime, (LONG)timerInterval, NULL, NULL, FALSE);
		//		if (res == 0) {
		//			showError("�� ������� ���������� �������� �������!");
		//		}
	}

	// ��������� �������
	void Timer::stopTimer()
	{
		//		BOOL res = CancelWaitableTimer(getEventHandle(evTimer));
		//		if (res == 0) {
		//			showError("�� ������� ���������� ������!");
		//		}
	}

	// ������ ������.
	HANDLE Timer::CreateTimer()
	{
		return HANDLE();
		//		HANDLE timerHandle = CreateWaitableTimer(NULL, FALSE, NULL);
		//		if (timerHandle == NULL) {
		//			showError("�� ���������� ������� ������.");
		//			exit(eecFailToCreateTimer);
		//		}
		//		return timerHandle;
	}

	void Timer::setTimerInterval(int msecs)
	{
		timerInterval = msecs;
	}
}