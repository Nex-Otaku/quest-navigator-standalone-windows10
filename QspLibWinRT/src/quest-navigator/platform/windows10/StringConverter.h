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

		// ����������� �����
		Platform::String^ convertFromString(string input);
	};
}