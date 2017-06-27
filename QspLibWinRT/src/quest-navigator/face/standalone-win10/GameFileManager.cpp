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

	void GameFileManager::inject(ApplicationPathReader* applicationPathReader)
	{
		this->applicationPathReader = applicationPathReader;
	}

	string GameFileManager::getDefaultGameFilePath()
	{
		return applicationPathReader->getApplicationFolderPath() + "\\game\\standalone_content\\game.qsp";
	}
}