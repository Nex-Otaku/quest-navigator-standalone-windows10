#include "pch.h"
#include "FileSystemApiWin32.h"
#include <string>
#include "..\..\core\encoding.h"
#include <Windows.h>

using namespace std;

namespace QuestNavigator {
	FileSystemApiWin32::FileSystemApiWin32()
	{
	}

	FileSystemApiWin32::~FileSystemApiWin32()
	{
	}

	bool FileSystemApiWin32::createDirectory(string path)
	{
		wstring wPath = widen(path);
		int res = CreateDirectory(wPath.c_str(), NULL);
		return res != 0;
	}

	bool FileSystemApiWin32::directoryExists(string path)
	{
		// ��������� ����� �� ������������� � ����������.
		// �����: ���������� �������� �������������� ����� �� �����, 
		// � ������� ��� �������.
		// ��� ������� ��������� ��� ������������� �������.
		DWORD dwAttrib = GetFileAttributes(widen(path).c_str());
		return ((dwAttrib != INVALID_FILE_ATTRIBUTES) &&
			(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	}
}