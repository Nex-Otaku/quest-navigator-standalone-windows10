#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {
	class FileSystemApiWin32
	{
	public:
		FileSystemApiWin32();
		~FileSystemApiWin32();

		// ������ �����.
		bool createDirectory(string path);
		// ��������� ����� �� �������������.
		bool directoryExists(string path);
		// ��������� ���� �� ������������� � ����������
		bool fileExists(string path);
	};
}
