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

		// ������������� ������������ ������ ��� ������
		bool build();

	private:
		GameFileManager* gameFileManager;
		StoragePathReader* storagePathReader;
		FileSystemManager* fileSystemManager;

		// ��������� ��������� ���� �� ����� config.xml
		bool loadGameConfig();
	};
}