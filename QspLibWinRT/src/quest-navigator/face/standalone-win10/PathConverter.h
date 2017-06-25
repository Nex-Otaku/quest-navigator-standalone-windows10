#pragma once

#include <string>
#include "..\..\platform\windows10\ApplicationPathReader.h"

using namespace std;

namespace QuestNavigator {
	class PathConverter
	{
	public:
		PathConverter();
		~PathConverter();

		void inject(ApplicationPathReader* applicationPathReader);

		string convertAbsolutePathToRelative(string path);

	private:
		ApplicationPathReader* applicationPathReader;
	};
}
