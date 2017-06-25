#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {
	class FileSystemApi
	{
	public:
		FileSystemApi();
		~FileSystemApi();

		bool createDirectory(string path);
	};
}
