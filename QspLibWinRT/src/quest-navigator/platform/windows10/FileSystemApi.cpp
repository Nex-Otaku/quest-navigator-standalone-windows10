#include "pch.h"
#include "FileSystemApi.h"
#include <string>
#include "..\..\core\encoding.h"
#include <Windows.h>

using namespace std;

namespace QuestNavigator {
	FileSystemApi::FileSystemApi()
	{
	}

	FileSystemApi::~FileSystemApi()
	{
	}

	bool FileSystemApi::createDirectory(string path)
	{
		wstring wPath = widen(path);
		int res = CreateDirectory(wPath.c_str(), NULL);
		return res != 0;
	}
}