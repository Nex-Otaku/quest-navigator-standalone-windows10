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

		// Пропускаем букву диска, если есть.
		pos = path.find_first_of(':', pos + 1);
		pos = pos == string::npos ? 0 : pos + 1;

		do
		{
			pos = path.find_first_of("\\/", pos + 1);
			string currentDir = pos == string::npos ? path : path.substr(0, pos);
			if (dirExists(currentDir)) {
				continue;
			}
			showError("createDirectory: " + currentDir);
			if (!fileSystemApi->createDirectory(currentDir)) {
				//return false;
			}
		} while (pos != string::npos);

//		return true;
		return dirExists(path);
	}
}