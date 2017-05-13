#pragma once

#include <vector>
#include <string>

using namespace std;

namespace QuestNavigator
{
	struct SaveSlotsDto
	{
		bool open;
		vector<string> slots;
	};
}