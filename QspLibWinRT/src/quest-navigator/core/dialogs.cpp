#include "dialogs.h"

namespace QuestNavigator {

	// Показываем системный диалог MessageBox.
	void showMessage(string msg, string title)
	{
		//wstring wMsg = widen(msg);
		//wstring wTitle = widen(title);
		//MessageBox(0, wMsg.c_str(), wTitle.c_str(), MB_OK);
	}

	// Отображаем ошибку.
	void showError(string msg)
	{
		showMessage(msg, "Ошибка");
	}
}