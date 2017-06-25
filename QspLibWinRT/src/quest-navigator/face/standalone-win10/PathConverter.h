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

		string absolutePathToRelativeUrl(string path);
		string absolutePathToRelativePath(string path);

	private:
		ApplicationPathReader* applicationPathReader;
	};
}
