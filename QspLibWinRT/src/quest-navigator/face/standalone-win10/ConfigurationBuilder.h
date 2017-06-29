#pragma once

#include "GameFileManager.h"
#include "..\..\platform\windows10\StoragePathReader.h"
#include "FileSystemManager.h"

namespace QuestNavigator
{
	class ConfigurationBuilder
	{
	public:
		ConfigurationBuilder();
		~ConfigurationBuilder();

		void inject(
			GameFileManager* gameFileManager,
			StoragePathReader* storagePathReader,
			FileSystemManager* fileSystemManager
		);

		// Устанавливаем конфигурацию плеера при старте
		bool build();

	private:
		GameFileManager* gameFileManager;
		StoragePathReader* storagePathReader;
		FileSystemManager* fileSystemManager;

		// Загружаем настройки игры из файла config.xml
		bool loadGameConfig();
	};
}