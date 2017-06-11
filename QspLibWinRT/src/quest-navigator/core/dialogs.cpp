#include "dialogs.h"
#include "..\platform\windows10\ErrorDebugReporter.h"

namespace QuestNavigator {

	// ���������� ��������� ������ MessageBox.
	void showMessage(string msg, string title)
	{
		//wstring wMsg = widen(msg);
		//wstring wTitle = widen(title);
		//MessageBox(0, wMsg.c_str(), wTitle.c_str(), MB_OK);
	}

	// ���������� ������.
	void showError(string msg)
	{
		// ��� ������� � Windows 10 ���������� ��������� �����.
		// showMessage(msg, "������");
		ErrorDebugReporter::instance()->showError(msg);
	}
}