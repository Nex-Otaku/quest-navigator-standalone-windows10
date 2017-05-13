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
		// Контекст UI
		if (!gameIsRunning) {
			this->eventManager->waitForLibIsReady();
		}

		// Передаём настройку из конфига в скин.
		int isGameStandalone = Configuration::getBool(ecpGameIsStandalone) ? 1 : 0;
		// Запускаем либо перезапускаем игру.
		this->eventManager->runGame(fileName, isGameStandalone);
		
		gameIsRunning = true;
	}

	void App::StopGame(bool restart)
	{
		//Контекст UI
		if (gameIsRunning)
		{
			// Мы должны иметь возможность остановить игру в любой момент.
			this->eventManager->stopGame();
			gameIsRunning = false;
		}
	}

	void App::runNewGame(string contentPath)
	{
		//		// Контекст UI
		//
		//		// Запускаем игру из нового пути, 
		//		// либо полностью перечитываем с диска существующую игру.
		//
		//		// Для начала, очищаем то, что уже запущено.
		//		FreeResources();
		//
		//		// Заново загружаем конфигурацию, копируем файлы.
		//		if (!initOptions(contentPath) || !prepareGameFiles()) {
		//			app_->Quit();
		//			return;
		//		}
		//
		//		// Обновляем свойства окна согласно настройкам шаблона.
		//		view_->applySkinToWindow();
		//
		//		// Запускаем поток библиотеки.
		//		initLib();
		//
		//		string url = QuestNavigator::getContentUrl();
		//		WebURL newUrl(ToWebString(url));
		//		WebView* webView = view_->web_view();
		//		if (newUrl == webView->url()) {
		//			// Очищаем кэш веб-содержимого.
		//			webView->session()->ClearCache();
		//			// Загружаем страницу заново, игнорируя закэшированные файлы.
		//			webView->Reload(true);
		//		} else {
		//			// Загружаем шаблон.
		//			webView->LoadURL(newUrl);
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
	}
}