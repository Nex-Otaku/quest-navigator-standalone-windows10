#pragma once

#include <string>
#include "..\..\platform\windows10\FileSystemApi.h"

using namespace std;

namespace QuestNavigator {
	class FileSystemManager
	{
	public:
		FileSystemManager();
		~FileSystemManager();

		void inject(FileSystemApi* fileSystemApi);

		// Создаём папки
		bool buildDirectoryPath(string path);

	private:
		FileSystemApi* fileSystemApi;
	};
}
