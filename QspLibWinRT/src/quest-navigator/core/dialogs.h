#pragma once

#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

namespace QuestNavigator {

	// ���������� ��������� ������ MessageBox.
	void showMessage(string msg, string title);
	// ���������� ������.
	void showError(string msg);
}