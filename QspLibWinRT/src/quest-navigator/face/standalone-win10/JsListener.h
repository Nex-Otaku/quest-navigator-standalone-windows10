#pragma once

#include <string>
#include "EventManager.h"
#include "App.h"
#include "Timer.h"
#include "JsExecutor.h"

using namespace std;

namespace QuestNavigator
{
	class JsListener
	{
	public:
		JsListener();
		~JsListener();

		void inject(
			EventManager* eventManager, 
			App* app,
			Timer* timer,
			JsExecutor* jsExecutor
		);

		void restartGame();
		void executeAction(int pos);
		void selectObject(int pos);
		void loadGame();
		void saveGame();
		void saveSlotSelected(int index, int mode);
		void msgResult();
		void errorResult();
		void userMenuResult(int pos);
		void inputResult(string text);
		void setMute(bool flag);
		void setInputString(string text);
		void runInputString();
		void runDefaultGame();

	private:
		EventManager* eventManager;
		App* app;
		Timer* timer;
		JsExecutor* jsExecutor;
	};
}