#pragma once

#include "JsListener.h"

using namespace QuestNavigator;

namespace QspLibWinRT
{
	public ref class QspLib sealed
	{
	public:
		QspLib();

		void restartGame();
		void executeAction(int32 pos);
		void selectObject(int32 pos);
		void loadGame();
		void saveGame();
		void saveSlotSelected(int32 index, int32 mode);
		void msgResult();
		void errorResult();
		void userMenuResult(int32 pos);
		void inputResult(Platform::String^ text);
		void setMute(Platform::Boolean flag);
		void setInputString(Platform::String^ text);
		void runInputString();
		void runDefaultGame();

	private:
		JsListener* jsListener;
	};
}
