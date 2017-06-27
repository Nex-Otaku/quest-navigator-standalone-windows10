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

		// ������������� ������������ ������ ��� ������
		bool build();

	private:
		GameFileManager* gameFileManager;
		StoragePathReader* storagePathReader;

		// ��������� ��������� ���� �� ����� config.xml
		bool loadGameConfig();
	};
}