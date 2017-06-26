#pragma once

#include "GameFileManager.h"
#include "..\..\platform\windows10\StoragePathReader.h"

namespace QuestNavigator
{
	class ConfigurationBuilder
	{
	public:
		ConfigurationBuilder();
		~ConfigurationBuilder();

		void inject(
			GameFileManager* gameFileManager,
			StoragePathReader* storagePathReader
		);

		// Устанавливаем конфигурацию плеера при старте
		bool build();

	private:
		GameFileManager* gameFileManager;
		StoragePathReader* storagePathReader;

		// Загружаем настройки игры из файла config.xml
		bool loadGameConfig();
	};
}