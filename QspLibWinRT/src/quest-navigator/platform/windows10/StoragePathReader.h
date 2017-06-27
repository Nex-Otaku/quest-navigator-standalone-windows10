#pragma once

#include <string>
#include "StringConverter.h"

using namespace std;

namespace QuestNavigator {
	class StoragePathReader
	{
	public:
		StoragePathReader();
		~StoragePathReader();

		void inject(StringConverter* stringConverter);

		string getStorageFolderPath();

	private:
		StringConverter* stringConverter;
	};
}