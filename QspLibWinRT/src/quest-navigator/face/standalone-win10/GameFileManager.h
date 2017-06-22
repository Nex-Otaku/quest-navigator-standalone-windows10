#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	class GameFileManager
	{
	public:
		GameFileManager();
		~GameFileManager();

		// Путь к файлу игры по умолчанию для standalone-приложения.
		string getDefaultGameFilePath();
	};
}