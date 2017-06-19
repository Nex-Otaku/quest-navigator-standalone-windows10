#pragma once

namespace QuestNavigator
{
	class GameFileManager
	{
	public:
		GameFileManager();
		~GameFileManager();

		// Загружаем файл игры по умолчанию для standalone-приложения.
		void loadDefaultGameFile();
	};
}