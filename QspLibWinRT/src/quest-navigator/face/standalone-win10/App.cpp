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
		EventManager* eventManager,
		Library* library
	)
	{
		this->eventManager = eventManager;
		this->library = library;
	}

	void App::init()
	{
		// Контекст UI
		
		if (!Configuration::init() 
			|| !initOptions("") 
			|| !prepareGameFiles() 
			/*|| !registerInstance()*/) {
			// STUB
			// Как аварийно завершить работу, пока не ясно.
			//app_->Quit();
			return;
		}
		
		// Проверяем обновления (не нужно в standalone)
		/*
		#ifdef _WIN32
		if (!Configuration::getBool(ecpGameIsStandalone)) {
			checkUpdate();
		}
		#endif
		*/
		
		//view_ = View::Create(Configuration::getInt(QuestNavigator::ecpGameWidth), Configuration::getInt(ecpGameHeight));
		
		// Перехватчик запросов, выполняющихся при нажатии на ссылку.
		//resource_interceptor_.setApp(app_);
		//app_->web_core()->set_resource_interceptor(&resource_interceptor_);
		
		initLib();
		
		// Привязываем обработку событий загрузки HTML-фреймов.
		// Интерфейс Awesomium::WebViewListener::Load.
		//view_->web_view()->set_load_listener(this);
		
		// Загружаем страницу с HTML, CSS и JS. 
		// В обработчике onDocumentReady привяжем глобальный JS-объект для библиотеки.
		// По завершению загрузки будет вызван обработчик onFinishLoadingFrame.
		//std::string url = QuestNavigator::getContentUrl();
		//view_->web_view()->LoadURL(WebURL(ToWebString(url)));
		
		//programLoaded = true;
	}

	void App::initLib()
	{
		// Контекст UI
		gameIsRunning = false;
		
		//Запускаем поток библиотеки
		this->library->StartLibThread();
	}

	void App::FreeResources()
	{
		// Контекст UI
		
		// Процедура "честного" высвобождения всех ресурсов - в т.ч. остановка потока библиотеки
		
		// Очищаем ВСЕ на выходе
		if (gameIsRunning)
		{
			StopGame(false);
		}
		// Останавливаем поток библиотеки
		this->library->StopLibThread();
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
		// Контекст UI
		
		// Запускаем игру из нового пути, 
		// либо полностью перечитываем с диска существующую игру.
		
		// Для начала, очищаем то, что уже запущено.
		FreeResources();
		
		// Заново загружаем конфигурацию, копируем файлы.
		if (!initOptions(contentPath) || !prepareGameFiles()) {
			//app_->Quit();
			// STUB
			// Сделать здесь вывод ошибок.
			return;
		}
		
		// Обновляем свойства окна согласно настройкам шаблона.
		//view_->applySkinToWindow();
		
		// Запускаем поток библиотеки.
		initLib();

		// !!! STUB
		// Этот код нам не нужен в standalone?
		// Каким образом перезагружаем страницу для полного обновления скина?

		//string url = QuestNavigator::getContentUrl();
		//WebURL newUrl(ToWebString(url));
		//WebView* webView = view_->web_view();
		//if (newUrl == webView->url()) {
		//	// Очищаем кэш веб-содержимого.
		//	webView->session()->ClearCache();
		//	// Загружаем страницу заново, игнорируя закэшированные файлы.
		//	webView->Reload(true);
		//} else {
		//	// Загружаем шаблон.
		//	webView->LoadURL(newUrl);
		//}
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