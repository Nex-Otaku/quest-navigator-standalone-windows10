#include "pch.h"
#include "FileSystemManager.h"
#include <string>
#include "..\..\core\files.h"
#include "..\..\core\dialogs.h"
#include "..\..\platform\windows10\FileSystemApiWin32.h"

using namespace std;

namespace QuestNavigator {
	FileSystemManager::FileSystemManager()
	{
	}

	FileSystemManager::~FileSystemManager()
	{
	}

	void FileSystemManager::inject(
		FileSystemApiWin32* fileSystemApiWin32
	)
	{
		this->fileSystemApiWin32 = fileSystemApiWin32;
	}

	// Создаём папки.
	bool FileSystemManager::buildDirectoryPath(string path)
	{
		unsigned int pos = 0;

		// Пропускаем букву диска, если есть.
		pos = path.find_first_of(':', pos + 1);
		pos = pos == string::npos ? 0 : pos + 1;

		// Так как мы не можем различить несуществующую папку и папку, к которой нет доступа,
		// то пытаемся создать все папки подряд.
		// Некрасиво, но других рабочих вариантов не существует.
		do
		{
			pos = path.find_first_of("\\/", pos + 1);
			string currentDir = pos == string::npos ? path : path.substr(0, pos);
			if (directoryExists(currentDir)) {
				continue;
			}
			fileSystemApiWin32->createDirectory(currentDir);
		} while (pos != string::npos);

		return directoryExists(path);
	}
	
	// Проверяем папку на существование.
	bool FileSystemManager::directoryExists(string path)
	{
		return fileSystemApiWin32->directoryExists(path);
	}
	
	bool FileSystemManager::fileExists(string path)
	{
		return fileSystemApiWin32->fileExists(path);
	}
}