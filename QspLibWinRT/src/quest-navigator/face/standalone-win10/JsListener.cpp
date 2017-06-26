#include "pch.h"
#include "JsListener.h"
#include "..\..\core\configuration.h"
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dialogs.h"

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
		JsExecutor* jsExecutor,
		SaveFileManager* saveFileManager
	)
	{
		this->eventManager = eventManager;
		this->app = app;
		this->timer = timer;
		this->jsExecutor = jsExecutor;
		this->saveFileManager = saveFileManager;
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
		showError("JsListener::loadGame");
		// Контекст UI

		// Останавливаем таймер
		this->timer->stopTimer();

		// Загружаем список файлов и отдаем в яваскрипт
		SaveSlotsDto dto = saveFileManager->getSaveSlots(true);
		this->jsExecutor->qspShowSaveSlotsDialog(dto);
	}

	void JsListener::saveGame()
	{
		showError("JsListener::saveGame");
		// Контекст UI

		// Останавливаем таймер
		this->timer->stopTimer();

		// Загружаем список файлов и отдаем в яваскрипт
		SaveSlotsDto dto = saveFileManager->getSaveSlots(false);
		this->jsExecutor->qspShowSaveSlotsDialog(dto);
	}

	void JsListener::saveSlotSelected(int index, int mode)
	{
		showError("JsListener::saveSlotSelected");
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
		// Контекст UI
		this->eventManager->msgClosed();
	}

	void JsListener::errorResult()
	{
		// Контекст UI
		this->eventManager->errorClosed();
	}

	void JsListener::userMenuResult(int pos)
	{
		// Контекст UI
		this->eventManager->menuClosed(pos);
	}

	void JsListener::inputResult(string text)
	{
		// Контекст UI
		this->eventManager->inputClosed(text);
	}

	void JsListener::setMute(bool flag)
	{
		// Контекст UI
		this->eventManager->mute(flag);
	}

	void JsListener::setInputString(string text)
	{
		// Контекст UI
		this->eventManager->inputStringChanged(text);
	}

	void JsListener::runInputString()
	{
		// Контекст UI
		// Нажали Enter в строке ввода
		this->eventManager->inputStringEntered();
	}

	void JsListener::runDefaultGame()
	{
		// Контекст UI
		// Запускаем игру по умолчанию.
		this->app->runNewGame("");
	}

	void JsListener::execLink(string text)
	{
		// Контекст UI
		// Выполняем код из ссылки "EXEC:".
		app->executeCode(text);
	}
}