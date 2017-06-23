#include "pch.h"
#include "GameFileManager.h"
#include <string>

using namespace std;

namespace QuestNavigator
{
	GameFileManager::GameFileManager()
	{
	}

	GameFileManager::~GameFileManager()
	{
	}

	void GameFileManager::inject(StringConverter* stringConverter)
	{
		this->stringConverter = stringConverter;
	}

	string GameFileManager::getDefaultGameFilePath()
	{
		// STUB
		return getApplicationFolderPath() + "\\game\\standalone_content\\game.qsp";
	}
	
	string GameFileManager::getApplicationFolderPath()
	{
		Windows::ApplicationModel::Package^ package = Windows::ApplicationModel::Package::Current;
		Windows::Storage::StorageFolder^ installedLocation = package->InstalledLocation;

		Platform::String^ path = installedLocation->Path;
		return stringConverter->convertUwpToStd(path);
	}
}