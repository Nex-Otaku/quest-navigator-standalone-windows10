#include "pch.h"
#include "JsListener.h"

namespace QuestNavigator
{

	JsListener::JsListener()
	{
	}

	JsListener::~JsListener()
	{
	}

	void JsListener::inject(EventManager * eventManager)
	{
		this->eventManager = eventManager;
	}

	// ��������� � API ������ �� ����������.

	void JsListener::restartGame()
	{
		// STUB
		//		// �������� UI
		//		string gameFile = Configuration::getString(ecpGameFilePath);
		//		StopGame(true);
		//		runGame(gameFile);
	}

	void JsListener::executeAction(int pos)
	{
		// STUB
		//		// �������� UI
		//		if (args.size() < 1) {
		//			showError("�� ������ �������� ��� executeAction!");
		//			return;
		//		}
		//
		//		if (!checkForSingle(evLibIsReady))
		//			return;
		//
		//		JSValue jsPos = args[0];
		//		int pos = jsPos.ToInteger();
		//		lockData();
		//		g_sharedData[evExecuteAction].num = pos;
		//		runSyncEvent(evExecuteAction);
		//		unlockData();
	}

	void JsListener::selectObject(int pos)
	{
		// STUB
		//		// �������� UI
		//		if (args.size() < 1) {
		//			showError("�� ������ �������� ��� selectObject!");
		//			return;
		//		}
		//		JSValue jsPos = args[0];
		//		int pos = jsPos.ToInteger();
		//
		//		if (!checkForSingle(evLibIsReady))
		//			return;
		//
		//		lockData();
		//		g_sharedData[evSelectObject].num = pos;
		//		runSyncEvent(evSelectObject);
		//		unlockData();
	}

	void JsListener::loadGame()
	{
		// STUB
		//		// �������� UI
		//		// ������������� ������
		//		stopTimer();
		//		// ��������� ������ ������ � ������ � ���������
		//		JSObject slots = getSaveSlots(true);
		//		qspShowSaveSlotsDialog(slots);
	}

	void JsListener::saveGame()
	{
		// STUB
		//		// �������� UI
		//		// ������������� ������
		//		stopTimer();
		//		// ��������� ������ ������ � ������ � ���������
		//		JSObject slots = getSaveSlots(false);
		//		qspShowSaveSlotsDialog(slots);
	}

	void JsListener::saveSlotSelected(int index, int mode)
	{
		// STUB
		//		// �������� UI
		//		if (args.size() < 2) {
		//			showError("�� ������� ��������� ��� saveSlotSelected!");
		//			return;
		//		}
		//		// ����� �����
		//		JSValue jsIndex = args[0];
		//		int index = jsIndex.ToInteger();
		//		// 1 - ��������, 0 - ����������
		//		JSValue jsMode = args[1];
		//		int mode = jsMode.ToInteger();
		//
		//		if (index == -1)
		//		{
		//			// ��������� ������
		//			startTimer();
		//			return;
		//		}
		//
		//		if (!checkForSingle(evLibIsReady))
		//			return;
		//
		//		if (mode == 1) {
		//			lockData();
		//			g_sharedData[evLoadSlotSelected].num = index;
		//			runSyncEvent(evLoadSlotSelected);
		//			unlockData();
		//		} else {
		//			lockData();
		//			g_sharedData[evSaveSlotSelected].num = index;
		//			runSyncEvent(evSaveSlotSelected);
		//			unlockData();
		//		}
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