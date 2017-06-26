#include "pch.h"
#include "FileSystemManager.h"
#include <string>
#include "..\..\core\files.h"
#include "..\..\core\dialogs.h"
#include "..\..\platform\windows10\FileSystemApi.h"

using namespace std;

namespace QuestNavigator {
	FileSystemManager::FileSystemManager()
	{
	}

	FileSystemManager::~FileSystemManager()
	{
	}

	void FileSystemManager::inject(FileSystemApi* fileSystemApi)
	{
		this->fileSystemApi = fileSystemApi;
	}

	// Создаём папки
	bool FileSystemManager::buildDirectoryPath(string path)
	{
		//if (dirExists(path)) {
		//	return true;
		//}
		//wstring wPath = widen(path);
		//int res = SHCreateDirectoryEx(NULL, wPath.c_str(), NULL);
		//return res == ERROR_SUCCESS;

		//return fileSystemApi->buildDirectoryPath(path);


		//// STUB
		//showError("buildDirectoryPath not implemented");
		//return true;

		unsigned int pos = 0;
		do
		{
			pos = path.find_first_of("\\/", pos + 1);
			if (dirExists(path)) {
				continue;
			}
			if (!fileSystemApi->createDirectory(path.substr(0, pos))) {
				return false;
			}
		} while (pos != std::string::npos);

		return true;
	}
}