#pragma once

#include <Windows.h>

namespace QuestNavigator {

	// ��������������� ������� ��� ������������� �������.

	// ������� �������
	bool waitForSingle(HANDLE handle);
	// ������������ ��������� � �������� ���� ��� �� ���.
	void freeHandle(HANDLE handle);
}