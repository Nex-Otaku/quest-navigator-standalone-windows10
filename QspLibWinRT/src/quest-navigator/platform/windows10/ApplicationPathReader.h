#pragma once

#include <string>
#include "StringConverter.h"

using namespace std;

namespace QuestNavigator {
	class ApplicationPathReader
	{
	public:
		ApplicationPathReader();
		~ApplicationPathReader();

		void inject(StringConverter* stringConverter);

		string getApplicationFolderPath();

	private:
		StringConverter* stringConverter;
	};
}

