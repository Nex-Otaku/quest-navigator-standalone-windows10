#include "dialogs.h"

namespace QuestNavigator {

	// ������ ��� �������� ����� ���� � �����.
	string openGameFileDialog(HWND hwnd)
	{
		//string filePath = "";

		//OPENFILENAME ofn;       // common dialog box structure
		//wchar_t wszFile[MAX_PATH];       // buffer for file name

		//// Initialize OPENFILENAME
		//ZeroMemory(&ofn, sizeof(ofn));
		//ofn.lStructSize = sizeof(ofn);
		//ofn.hwndOwner = hwnd;
		//ofn.lpstrFile = wszFile;
		//// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
		//// use the contents of szFile to initialize itself.
		//ofn.lpstrFile[0] = '\0';
		//ofn.nMaxFile = sizeof(wszFile);
		//string extensions = "���� QSP (*.QSP)\r*.QSP\r���������� ������ (*.GAM)\r*.GAM\r";
		//wstring wExtensions = widen(extensions);
		//// ������ \r �� ������� ����. 
		//// ���� � �������� ������ ����� ������� ������� ����,
		//// �� ��� ��������� ��� �����������.
		//std::replace(wExtensions.begin(), wExtensions.end(), '\r', '\0');
		//ofn.lpstrFilter = wExtensions.c_str();
		//ofn.nFilterIndex = 1;
		//ofn.lpstrFileTitle = NULL;
		//ofn.nMaxFileTitle = 0;
		//ofn.lpstrInitialDir = NULL;
		//ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		//// Display the Open dialog box. 

		//BOOL res = GetOpenFileName(&ofn);
		//if (res == 0) {
		//	DWORD dwError = CommDlgExtendedError();
		//	if (dwError != 0) {
		//		showError("������ ��� �������� �����");
		//	}
		//	return "";
		//}

		//// ���������� ��� ��������� �����.
		//wstring wFilePath = ofn.lpstrFile;
		//filePath = narrow(wFilePath);
		//return filePath;
	}
}