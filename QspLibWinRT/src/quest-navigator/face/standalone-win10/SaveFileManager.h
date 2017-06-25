#pragma once

#include <string>
#include "Library.h"
#include "FileSystemManager.h"

using namespace std;

namespace QuestNavigator {
	class SaveFileManager
	{
	public:
		SaveFileManager();
		~SaveFileManager();

		void inject(
			Library* library,
			FileSystemManager* fileSystemManager
		);

		bool readSaveFile(string relativePath, bool refresh);
		bool writeSaveFile(string relativePath);

	private:
		Library* library;
		FileSystemManager* fileSystemManager;

		string getFullSavePath(string relativePath);
	};
}
