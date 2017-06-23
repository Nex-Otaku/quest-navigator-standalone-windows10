#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	class StringConverter
	{
	public:
		StringConverter();
		~StringConverter();

		// Конвертация строк
		Platform::String^ convertStdToUwp(string input);
		string convertUwpToStd(Platform::String^ input);
	};
}