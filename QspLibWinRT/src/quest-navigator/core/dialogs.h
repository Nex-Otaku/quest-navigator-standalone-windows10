#pragma once

#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

namespace QuestNavigator {
	// ������ ��� �������� ����� ���� � �����.
	string openGameFileDialog(HWND hWnd);

	// ���������� ��������� ������ MessageBox.
	void showMessage(string msg, string title);
	// ���������� ������.
	void showError(string msg);
}