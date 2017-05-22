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
		// �������� UI
		
		if (!Configuration::init() 
			|| !initOptions("") 
			|| !prepareGameFiles() 
			/*|| !registerInstance()*/) {
			// STUB
			// ��� �������� ��������� ������, ���� �� ����.
			//app_->Quit();
			return;
		}
		
		// ��������� ���������� (�� ����� � standalone)
		/*
		#ifdef _WIN32
		if (!Configuration::getBool(ecpGameIsStandalone)) {
			checkUpdate();
		}
		#endif
		*/
		
		//view_ = View::Create(Configuration::getInt(QuestNavigator::ecpGameWidth), Configuration::getInt(ecpGameHeight));
		
		// ����������� ��������, ������������� ��� ������� �� ������.
		//resource_interceptor_.setApp(app_);
		//app_->web_core()->set_resource_interceptor(&resource_interceptor_);
		
		initLib();
		
		// ����������� ��������� ������� �������� HTML-�������.
		// ��������� Awesomium::WebViewListener::Load.
		//view_->web_view()->set_load_listener(this);
		
		// ��������� �������� � HTML, CSS � JS. 
		// � ����������� onDocumentReady �������� ���������� JS-������ ��� ����������.
		// �� ���������� �������� ����� ������ ���������� onFinishLoadingFrame.
		//std::string url = QuestNavigator::getContentUrl();
		//view_->web_view()->LoadURL(WebURL(ToWebString(url)));
		
		//programLoaded = true;
	}

	void App::initLib()
	{
		// �������� UI
		gameIsRunning = false;
		
		//��������� ����� ����������
		this->library->StartLibThread();
	}

	void App::FreeResources()
	{
		// �������� UI
		
		// ��������� "��������" ������������� ���� �������� - � �.�. ��������� ������ ����������
		
		// ������� ��� �� ������
		if (gameIsRunning)
		{
			StopGame(false);
		}
		// ������������� ����� ����������
		this->library->StopLibThread();
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
		// �������� UI
		
		// ��������� ���� �� ������ ����, 
		// ���� ��������� ������������ � ����� ������������ ����.
		
		// ��� ������, ������� ��, ��� ��� ��������.
		FreeResources();
		
		// ������ ��������� ������������, �������� �����.
		if (!initOptions(contentPath) || !prepareGameFiles()) {
			//app_->Quit();
			// STUB
			// ������� ����� ����� ������.
			return;
		}
		
		// ��������� �������� ���� �������� ���������� �������.
		//view_->applySkinToWindow();
		
		// ��������� ����� ����������.
		initLib();

		// !!! STUB
		// ���� ��� ��� �� ����� � standalone?
		// ����� ������� ������������� �������� ��� ������� ���������� �����?

		//string url = QuestNavigator::getContentUrl();
		//WebURL newUrl(ToWebString(url));
		//WebView* webView = view_->web_view();
		//if (newUrl == webView->url()) {
		//	// ������� ��� ���-�����������.
		//	webView->session()->ClearCache();
		//	// ��������� �������� ������, ��������� �������������� �����.
		//	webView->Reload(true);
		//} else {
		//	// ��������� ������.
		//	webView->LoadURL(newUrl);
		//}
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