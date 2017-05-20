#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	struct ErrorDto
	{
		string desc;
		string loc;
		int actIndex;
		int line;
	};
}