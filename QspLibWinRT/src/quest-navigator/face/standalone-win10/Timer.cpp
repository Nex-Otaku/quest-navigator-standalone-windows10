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
}