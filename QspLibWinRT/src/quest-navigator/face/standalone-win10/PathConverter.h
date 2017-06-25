#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {
	class PathConverter
	{
	public:
		PathConverter();
		~PathConverter();

		string convertAbsolutePathToRelative(string path);
	};
}
