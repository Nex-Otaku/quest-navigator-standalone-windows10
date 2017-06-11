#include "dialogs.h"
#include "..\platform\windows10\ErrorDebugReporter.h"

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
		// Для отладки в Windows 10 подключаем отдельный класс.
		// showMessage(msg, "Ошибка");
		ErrorDebugReporter::instance()->showError(msg);
	}
}