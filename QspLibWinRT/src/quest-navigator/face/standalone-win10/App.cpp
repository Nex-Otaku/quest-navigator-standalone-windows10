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
		:gameIsRunning(false)
	{
	}

	App::~App()
	{
	}

	void App::inject(
		EventManager* eventManager
	)
	{
		this->eventManager = eventManager;
	}

	void App::runGame(string fileName)
	{
		// �������� UI
		if (!gameIsRunning) {
			this->eventManager->waitForLibIsReady();
		}

		// ������� ��������� �� ������� � ����.
		int isGameStandalone = Configuration::getBool(ecpGameIsStandalone) ? 1 : 0;
		// ��������� ���� ������������� ����.
		this->eventManager->runGame(fileName, isGameStandalone);
		
		gameIsRunning = true;
	}

	void App::StopGame(bool restart)
	{
		//�������� UI
		if (gameIsRunning)
		{
			// �� ������ ����� ����������� ���������� ���� � ����� ������.
			this->eventManager->stopGame();
			gameIsRunning = false;
		}
	}

	void App::runNewGame(string contentPath)
	{
		//		// �������� UI
		//
		//		// ��������� ���� �� ������ ����, 
		//		// ���� ��������� ������������ � ����� ������������ ����.
		//
		//		// ��� ������, ������� ��, ��� ��� ��������.
		//		FreeResources();
		//
		//		// ������ ��������� ������������, �������� �����.
		//		if (!initOptions(contentPath) || !prepareGameFiles()) {
		//			app_->Quit();
		//			return;
		//		}
		//
		//		// ��������� �������� ���� �������� ���������� �������.
		//		view_->applySkinToWindow();
		//
		//		// ��������� ����� ����������.
		//		initLib();
		//
		//		string url = QuestNavigator::getContentUrl();
		//		WebURL newUrl(ToWebString(url));
		//		WebView* webView = view_->web_view();
		//		if (newUrl == webView->url()) {
		//			// ������� ��� ���-�����������.
		//			webView->session()->ClearCache();
		//			// ��������� �������� ������, ��������� �������������� �����.
		//			webView->Reload(true);
		//		} else {
		//			// ��������� ������.
		//			webView->LoadURL(newUrl);
		//		}
	}

	SaveSlotsDto App::getSaveSlots(bool open)
	{
		//�������� UI
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
	}
}