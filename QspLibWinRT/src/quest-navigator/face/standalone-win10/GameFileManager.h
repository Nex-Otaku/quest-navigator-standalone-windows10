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

		// ���� � ����� ���� �� ��������� ��� standalone-����������.
		string getDefaultGameFilePath();
	};
}