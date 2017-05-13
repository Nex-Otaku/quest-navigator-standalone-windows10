#include "pch.h"
#include "JsListener.h"
#include "..\..\core\configuration.h"
#include "dto\SaveSlotsDto.h"

namespace QuestNavigator
{

	JsListener::JsListener()
	{
	}

	JsListener::~JsListener()
	{
	}

	void JsListener::inject(
		EventManager* eventManager, 
		App* app,
		Timer* timer,
		JsExecutor* jsExecutor
	)
	{
		this->eventManager = eventManager;
		this->app = app;
		this->timer = timer;
		this->jsExecutor = jsExecutor;
	}

	// Обращение к API плеера из яваскрипта.

	void JsListener::restartGame()
	{
		// Контекст UI
		string gameFile = Configuration::getString(ecpGameFilePath);
		app->StopGame(true);
		app->runGame(gameFile);
	}

	void JsListener::executeAction(int pos)
	{
		// Контекст UI
		this->eventManager->executeAction(pos);
	}

	void JsListener::selectObject(int pos)
	{
		// Контекст UI
		this->eventManager->selectObject(pos);
	}

	void JsListener::loadGame()
	{
		// Контекст UI

		// Останавливаем таймер
		this->timer->stopTimer();

		// Загружаем список файлов и отдаем в яваскрипт
		SaveSlotsDto dto = this->app->getSaveSlots(true);
		this->jsExecutor->qspShowSaveSlotsDialog(dto);
	}

	void JsListener::saveGame()
	{
		// Контекст UI

		// Останавливаем таймер
		this->timer->stopTimer();

		// Загружаем список файлов и отдаем в яваскрипт
		SaveSlotsDto dto = this->app->getSaveSlots(false);
		this->jsExecutor->qspShowSaveSlotsDialog(dto);
	}

	void JsListener::saveSlotSelected(int index, int mode)
	{
		// Контекст UI

		// Если номер слота "-1", 
		// значит, диалог был отменён.
		if (index == -1)
		{
			// Запускаем таймер
			this->timer->startTimer();
			return;
		}
		
		// 1 - загрузка, 0 - сохранение
		if (mode == 1) {
			this->eventManager->loadSlotSelected(index);
		} else {
			this->eventManager->saveSlotSelected(index);
		}
	}

	void JsListener::msgResult()
	{
		// STUB
		//		// Контекст UI
		//		runSyncEvent(evMsgClosed);
	}

	void JsListener::errorResult()
	{
		// STUB
		//		// Контекст UI
		//		runSyncEvent(evErrorClosed);
	}

	void JsListener::userMenuResult(int pos)
	{
		// STUB
		//		// Контекст UI
		//		if (args.size() < 1) {
		//			showError("Не указан параметр для userMenuResult!");
		//			return;
		//		}
		//		JSValue jsPos = args[0];
		//		int pos = jsPos.ToInteger();
		//
		//		lockData();
		//		g_sharedData[evMenuClosed].num = pos;
		//		runSyncEvent(evMenuClosed);
		//		unlockData();
	}

	void JsListener::inputResult(string text)
	{
		// STUB
		//		// Контекст UI
		//		if (args.size() < 1) {
		//			showError("Не указан параметр для inputResult!");
		//			return;
		//		}
		//		JSValue jsText = args[0];
		//		string text = ToString(jsText.ToString());
		//
		//		lockData();
		//		g_sharedData[evInputClosed].str = text;
		//		runSyncEvent(evInputClosed);
		//		unlockData();
	}

	void JsListener::setMute(bool flag)
	{
		// STUB
		//		// Контекст UI
		//		if (args.size() < 1) {
		//			showError("Не указан параметр для setMute!");
		//			return;
		//		}
		//		JSValue jsFlag = args[0];
		//		bool flag = jsFlag.ToBoolean();
		//
		//		lockData();
		//		g_sharedData[evMute].flag = flag;
		//		runSyncEvent(evMute);
		//		unlockData();
	}

	void JsListener::setInputString(string text)
	{
		// STUB
		//		// Контекст UI
		//		// Изменился текст в строке ввода
		//		if (args.size() < 1) {
		//			showError("Не указан параметр для setInputString!");
		//			return;
		//		}
		//		JSValue jsText = args[0];
		//		string text = ToString(jsText.ToString());
		//
		//		lockData();
		//		g_sharedData[evInputStringChanged].str = text;
		//		runSyncEvent(evInputStringChanged);
		//		unlockData();
	}

	void JsListener::runInputString()
	{
		// STUB
		//		// Контекст UI
		//		// Нажали Enter в строке ввода
		//		runSyncEvent(evInputStringEntered);
	}

	void JsListener::runDefaultGame()
	{
		// STUB
		//		// Контекст UI
		//
		//		// Запускаем игру по умолчанию.
		//		runNewGame("");
	}
}