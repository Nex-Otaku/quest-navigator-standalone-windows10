#pragma once

namespace QuestNavigator
{
	class GameFileManager
	{
	public:
		GameFileManager();
		~GameFileManager();

		// ��������� ���� ���� �� ��������� ��� standalone-����������.
		void loadDefaultGameFile();
	};
}