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

	// Обращение к API плеера из яваскрипта.

	void JsListener::restartGame()
	{
		// STUB
		//		// Контекст UI
		//		string gameFile = Configuration::getString(ecpGameFilePath);
		//		StopGame(true);
		//		runGame(gameFile);
	}

	void JsListener::executeAction(int pos)
	{
		// STUB
		//		// Контекст UI
		//		if (args.size() < 1) {
		//			showError("Не указан параметр для executeAction!");
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
		//		// Контекст UI
		//		if (args.size() < 1) {
		//			showError("Не указан параметр для selectObject!");
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
		//		// Контекст UI
		//		// Останавливаем таймер
		//		stopTimer();
		//		// Загружаем список файлов и отдаем в яваскрипт
		//		JSObject slots = getSaveSlots(true);
		//		qspShowSaveSlotsDialog(slots);
	}

	void JsListener::saveGame()
	{
		// STUB
		//		// Контекст UI
		//		// Останавливаем таймер
		//		stopTimer();
		//		// Загружаем список файлов и отдаем в яваскрипт
		//		JSObject slots = getSaveSlots(false);
		//		qspShowSaveSlotsDialog(slots);
	}

	void JsListener::saveSlotSelected(int index, int mode)
	{
		// STUB
		//		// Контекст UI
		//		if (args.size() < 2) {
		//			showError("Не указаны параметры для saveSlotSelected!");
		//			return;
		//		}
		//		// Номер слота
		//		JSValue jsIndex = args[0];
		//		int index = jsIndex.ToInteger();
		//		// 1 - загрузка, 0 - сохранение
		//		JSValue jsMode = args[1];
		//		int mode = jsMode.ToInteger();
		//
		//		if (index == -1)
		//		{
		//			// Запускаем таймер
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