#pragma once

#include "JsListener.h"
#include "..\..\platform\windows10\UwpJsExecutor.h"

using namespace QuestNavigator;

using namespace Windows::Foundation;


namespace QspLibWinRT
{
	public ref class QspLib sealed
	{
	public:
		QspLib();

		void init();

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

		void execLink(Platform::String^ text);

		IAsyncAction^ RestartGameAsync();

		// Метод для отладки
		void callDebugMessage();

		// Объект для привязки колбеков.
		UwpJsExecutor^ getUwpJsExecutor();
	private:
		App* app;
		JsListener* jsListener;
		UwpJsExecutor^ uwpJsExecutor;
		StringConverter* stringConverter;
	};
}
