#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {
	class FileSystemApiWin32
	{
	public:
		FileSystemApiWin32();
		~FileSystemApiWin32();

		// Создаём папку.
		bool createDirectory(string path);
		// Проверяем папку на существование.
		bool directoryExists(string path);
		// Проверяем файл на существование и читаемость
		bool fileExists(string path);
	};
}
