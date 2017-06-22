#pragma once

#include "GameFileManager.h"

namespace QuestNavigator
{
	class ConfigurationBuilder
	{
	public:
		ConfigurationBuilder();
		~ConfigurationBuilder();

		void inject(
			GameFileManager* gameFileManager
		);

		// Устанавливаем конфигурацию плеера при старте
		bool build();

	private:
		GameFileManager* gameFileManager;

		// Загружаем настройки игры из файла config.xml
		bool loadGameConfig();
	};
}