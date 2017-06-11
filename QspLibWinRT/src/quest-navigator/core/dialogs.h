#pragma once

#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

namespace QuestNavigator {

	// Показываем системный диалог MessageBox.
	void showMessage(string msg, string title);
	// Отображаем ошибку.
	void showError(string msg);
}