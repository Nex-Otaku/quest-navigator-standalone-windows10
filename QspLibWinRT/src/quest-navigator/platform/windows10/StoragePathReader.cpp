#include "pch.h"
#include "StoragePathReader.h"
#include "ApplicationPathReader.h"
#include <string>

using namespace std;

namespace QuestNavigator {
	StoragePathReader::StoragePathReader()
	{
	}

	StoragePathReader::~StoragePathReader()
	{
	}

	void StoragePathReader::inject(StringConverter* stringConverter)
	{
		this->stringConverter = stringConverter;
	}

	string StoragePathReader::getStorageFolderPath()
	{
		Windows::Storage::StorageFolder^ localFolder = Windows::Storage::ApplicationData::Current->LocalFolder;

		Platform::String^ path = localFolder->Path;
		return stringConverter->convertUwpToStd(path);
	}
}