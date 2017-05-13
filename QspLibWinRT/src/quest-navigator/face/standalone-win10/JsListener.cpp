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

	// ��������� � API ������ �� ����������.

	void JsListener::restartGame()
	{
		// �������� UI
		string gameFile = Configuration::getString(ecpGameFilePath);
		app->StopGame(true);
		app->runGame(gameFile);
	}

	void JsListener::executeAction(int pos)
	{
		// �������� UI
		this->eventManager->executeAction(pos);
	}

	void JsListener::selectObject(int pos)
	{
		// �������� UI
		this->eventManager->selectObject(pos);
	}

	void JsListener::loadGame()
	{
		// �������� UI

		// ������������� ������
		this->timer->stopTimer();

		// ��������� ������ ������ � ������ � ���������
		SaveSlotsDto dto = this->app->getSaveSlots(true);
		this->jsExecutor->qspShowSaveSlotsDialog(dto);
	}

	void JsListener::saveGame()
	{
		// �������� UI

		// ������������� ������
		this->timer->stopTimer();

		// ��������� ������ ������ � ������ � ���������
		SaveSlotsDto dto = this->app->getSaveSlots(false);
		this->jsExecutor->qspShowSaveSlotsDialog(dto);
	}

	void JsListener::saveSlotSelected(int index, int mode)
	{
		// �������� UI

		// ���� ����� ����� "-1", 
		// ������, ������ ��� ������.
		if (index == -1)
		{
			// ��������� ������
			this->timer->startTimer();
			return;
		}
		
		// 1 - ��������, 0 - ����������
		if (mode == 1) {
			this->eventManager->loadSlotSelected(index);
		} else {
			this->eventManager->saveSlotSelected(index);
		}
	}

	void JsListener::msgResult()
	{
		// �������� UI
		this->eventManager->msgClosed();
	}

	void JsListener::errorResult()
	{
		// �������� UI
		this->eventManager->errorClosed();
	}

	void JsListener::userMenuResult(int pos)
	{
		// �������� UI
		this->eventManager->menuClosed(pos);
	}

	void JsListener::inputResult(string text)
	{
		// �������� UI
		this->eventManager->inputClosed(text);
	}

	void JsListener::setMute(bool flag)
	{
		// �������� UI
		this->eventManager->mute(flag);
	}

	void JsListener::setInputString(string text)
	{
		// �������� UI
		this->eventManager->inputStringChanged(text);
	}

	void JsListener::runInputString()
	{
		// �������� UI
		// ������ Enter � ������ �����
		this->eventManager->inputStringEntered();
	}

	void JsListener::runDefaultGame()
	{
		// �������� UI
		// ��������� ���� �� ���������.
		this->app->runNewGame("");
	}
}