#pragma once

#include <string>
#include "..\..\platform\windows10\FileSystemApiWin32.h"

using namespace std;

namespace QuestNavigator {
	class FileSystemManager
	{
	public:
		FileSystemManager();
		~FileSystemManager();

		void inject(
			FileSystemApiWin32* fileSystemApiWin32
		);

		// Создаём папки
		bool buildDirectoryPath(string path);
		// Проверяем папку на существование.
		bool directoryExists(string path);

	private:
		FileSystemApiWin32* fileSystemApiWin32;
	};
}
