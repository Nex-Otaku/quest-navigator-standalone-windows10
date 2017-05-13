#include "pch.h"
#include "App.h"
#include "..\..\core\configuration.h"
#include "..\..\core\files.h"
#include "..\..\core\utils.h"
#include <vector>
#include <string>

using namespace std;

namespace QuestNavigator
{

	App::App()
	{
	}

	App::~App()
	{
	}

	void App::runGame(string fileName)
	{
		//		// Контекст UI
		//		if (gameIsRunning) {
		//			if (!checkForSingle(evLibIsReady))
		//				return;
		//		} else {
		//			waitForSingle(evLibIsReady);
		//		}
		//
		//		// Готовим данные для передачи в поток
		//		lockData();
		//		g_sharedData[evRunGame].str = fileName;
		//		// Передаём настройку из конфига в скин.
		//		g_sharedData[evRunGame].num = Configuration::getBool(ecpGameIsStandalone) ? 1 : 0;
		//		runSyncEvent(evRunGame);
		//		unlockData();
		//
		//		gameIsRunning = true;
		//
		//		// Если плеер не запущен в режиме "standalone",
		//		// и запущена игра не по умолчанию,
		//		// то записываем время последнего запуска в БД.
		//		if (!Configuration::getBool(ecpGameIsStandalone)
		//			&& !Configuration::getBool(ecpRunningDefaultGame)) {
		//			GamestockEntry game;
		//			// Пока что запускаем только локальные игры.
		//			game.web = false;
		//			game.local_file = Configuration::getString(ecpGameFilePath);
		//			game.title = Configuration::getString(ecpGameTitle);
		//			game.hash = Configuration::getString(ecpGameHash);
		//			game.cache = Configuration::getString(ecpCacheDir);
		//			game.saves = Configuration::getString(ecpSaveDir);
		//			game.last_run = (int)time(0);
		//			Gamestock::updateGame(game);
		//		}
	}

	void App::StopGame(bool restart)
	{
		//		//Контекст UI
		//		if (gameIsRunning)
		//		{
		//			// Мы должны иметь возможность остановить игру в любой момент.
		//			runSyncEvent(evStopGame);
		//			waitForSingle(evGameStopped);
		//			gameIsRunning = false;
		//		}
	}

	SaveSlotsDto App::getSaveSlots(bool open)
	{
		//Контекст UI
		SaveSlotsDto dto;
		vector<string> slots;

		int maxSlots = Configuration::getInt(ecpSaveSlotMax);
		for (int i = 0; i < maxSlots; i++)
		{
			string title;
			string slotname = to_string(i + 1) + ".sav";
			string slotpath = getRightPath(Configuration::getString(ecpSaveDir) + PATH_DELIMITER + slotname);
			if (fileExists(slotpath))
				title = to_string(i + 1);
			else
				title = "-empty-";
			slots.push_back(title);
		}

		dto.open = open;
		dto.slots = slots;

		return dto;

		//		//Контекст UI
		//		JSArray jsSlots;
		//		int maxSlots = Configuration::getInt(ecpSaveSlotMax);
		//		for (int i = 0; i < maxSlots; i++)
		//		{
		//			string title;
		//			string slotname = to_string(i + 1) + ".sav";
		//			string slotpath = getRightPath(Configuration::getString(ecpSaveDir) + PATH_DELIMITER + slotname);
		//			if (fileExists(slotpath))
		//				title = to_string(i + 1);
		//			else
		//				title = "-empty-";
		//			jsSlots.Push(ToWebString(title));
		//		}
		//
		//		JSObject jsSlotsContainer;
		//		jsSlotsContainer.SetProperty(WSLit("open"), JSValue(open ? 1 : 0));
		//		jsSlotsContainer.SetProperty(WSLit("slots"), jsSlots);
		//		return jsSlotsContainer;
	}
}