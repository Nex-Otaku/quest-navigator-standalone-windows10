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

	string GameFileManager::getDefaultGameFilePath()
	{
		// STUB
		return "game\\standalone_content\\game.qsp";
	}
}