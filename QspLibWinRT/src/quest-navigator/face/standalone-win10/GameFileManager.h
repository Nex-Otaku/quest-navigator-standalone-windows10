#pragma once

#include <string>
#include "..\..\platform\windows10\ApplicationPathReader.h"

using namespace std;

namespace QuestNavigator
{
	class GameFileManager
	{
	public:
		GameFileManager();
		~GameFileManager();

		void inject(ApplicationPathReader* applicationPathReader);

		// ���� � ����� ���� �� ��������� ��� standalone-����������.
		string getDefaultGameFilePath();

	private:
		ApplicationPathReader* applicationPathReader;
	};
}