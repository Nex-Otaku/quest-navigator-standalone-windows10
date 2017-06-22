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

		// ������������� ������������ ������ ��� ������
		bool build();

	private:
		GameFileManager* gameFileManager;

		// ��������� ��������� ���� �� ����� config.xml
		bool loadGameConfig();
	};
}