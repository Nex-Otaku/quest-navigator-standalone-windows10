#include "pch.h"
#include "App.h"

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
		//		// �������� UI
		//		if (gameIsRunning) {
		//			if (!checkForSingle(evLibIsReady))
		//				return;
		//		} else {
		//			waitForSingle(evLibIsReady);
		//		}
		//
		//		// ������� ������ ��� �������� � �����
		//		lockData();
		//		g_sharedData[evRunGame].str = fileName;
		//		// ������� ��������� �� ������� � ����.
		//		g_sharedData[evRunGame].num = Configuration::getBool(ecpGameIsStandalone) ? 1 : 0;
		//		runSyncEvent(evRunGame);
		//		unlockData();
		//
		//		gameIsRunning = true;
		//
		//		// ���� ����� �� ������� � ������ "standalone",
		//		// � �������� ���� �� �� ���������,
		//		// �� ���������� ����� ���������� ������� � ��.
		//		if (!Configuration::getBool(ecpGameIsStandalone)
		//			&& !Configuration::getBool(ecpRunningDefaultGame)) {
		//			GamestockEntry game;
		//			// ���� ��� ��������� ������ ��������� ����.
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
		//		//�������� UI
		//		if (gameIsRunning)
		//		{
		//			// �� ������ ����� ����������� ���������� ���� � ����� ������.
		//			runSyncEvent(evStopGame);
		//			waitForSingle(evGameStopped);
		//			gameIsRunning = false;
		//		}
	}
}