#pragma once

#include <string>
#include "Library.h"
#include "FileSystemManager.h"

using namespace std;

namespace QuestNavigator {
	// Объявляем класс, чтобы избежать циклической зависимости.
	// Класс будет определён позже в соответствующем заголовочном файле.
	class Library;

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
		SaveSlotsDto getSaveSlots(bool open);

	private:
		Library* library;
		FileSystemManager* fileSystemManager;

		string getFullSavePath(string relativePath);
	};
}
