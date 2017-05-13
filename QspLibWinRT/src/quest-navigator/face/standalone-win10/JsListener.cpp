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
		// STUB
		//		// �������� UI
		//		runSyncEvent(evMsgClosed);
	}

	void JsListener::errorResult()
	{
		// STUB
		//		// �������� UI
		//		runSyncEvent(evErrorClosed);
	}

	void JsListener::userMenuResult(int pos)
	{
		// STUB
		//		// �������� UI
		//		if (args.size() < 1) {
		//			showError("�� ������ �������� ��� userMenuResult!");
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
		//		// �������� UI
		//		if (args.size() < 1) {
		//			showError("�� ������ �������� ��� inputResult!");
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
		//		// �������� UI
		//		if (args.size() < 1) {
		//			showError("�� ������ �������� ��� setMute!");
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
		//		// �������� UI
		//		// ��������� ����� � ������ �����
		//		if (args.size() < 1) {
		//			showError("�� ������ �������� ��� setInputString!");
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
		//		// �������� UI
		//		// ������ Enter � ������ �����
		//		runSyncEvent(evInputStringEntered);
	}

	void JsListener::runDefaultGame()
	{
		// STUB
		//		// �������� UI
		//
		//		// ��������� ���� �� ���������.
		//		runNewGame("");
	}
}