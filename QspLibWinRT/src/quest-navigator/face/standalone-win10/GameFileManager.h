#pragma once

#include <string>
#include "..\..\platform\windows10\StringConverter.h"

using namespace std;

namespace QuestNavigator
{
	class GameFileManager
	{
	public:
		GameFileManager();
		~GameFileManager();

		void inject(StringConverter* stringConverter);

		// ���� � ����� ���� �� ��������� ��� standalone-����������.
		string getDefaultGameFilePath();

	private:
		StringConverter* stringConverter;

		string getApplicationFolderPath();
	};
}