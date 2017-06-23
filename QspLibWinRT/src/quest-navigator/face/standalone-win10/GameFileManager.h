#pragma once

#include <string>
#include "..\..\platform\windows10\StringConverter.h"

using namespace std;

namespace QuestNavigator
{
	class GameFileManager
	{
	public:
		GameFileManager();
		~GameFileManager();

		void inject(StringConverter* stringConverter);

		// Путь к файлу игры по умолчанию для standalone-приложения.
		string getDefaultGameFilePath();

	private:
		StringConverter* stringConverter;

		string getApplicationFolderPath();
	};
}