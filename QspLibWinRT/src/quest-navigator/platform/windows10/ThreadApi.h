#pragma once

/*
���� ������� ��� ������� ������ � ��������,
������� ������� �� ������������ ���������.

���������� ���������, �������� ������ - �� Win32 ��� ���� �������, �� WinRT ������.

����� ������ ������ ������, ��� ������ ������.
��� �� ������ ������������� � ������ ������ ������������� ������� �� ������ ��� ������������� ���������� ����.
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
