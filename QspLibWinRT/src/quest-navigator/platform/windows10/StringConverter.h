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
		Platform::String^ convertFromString(string input);
	};
}