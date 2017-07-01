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

		// Метод для отладки
		void callDebugMessage();

		// Объект для привязки колбеков.
		UwpJsExecutor^ getUwpJsExecutor();
	private:
		App* app;
		JsListener* jsListener;
		UwpJsExecutor^ uwpJsExecutor;
		StringConverter* stringConverter;

		// Обработка вызовов API в фоновом потоке.

		IAsyncAction^ initAsync();

		IAsyncAction^ restartGameAsync();
		IAsyncAction^ executeActionAsync(int32 pos);
		IAsyncAction^ selectObjectAsync(int32 pos);
		IAsyncAction^ loadGameAsync();
		IAsyncAction^ saveGameAsync();
		IAsyncAction^ saveSlotSelectedAsync(int32 index, int32 mode);
		IAsyncAction^ msgResultAsync();
		IAsyncAction^ errorResultAsync();
		IAsyncAction^ userMenuResultAsync(int32 pos);
		IAsyncAction^ inputResultAsync(Platform::String^ text);
		IAsyncAction^ setMuteAsync(Platform::Boolean flag);
		IAsyncAction^ setInputStringAsync(Platform::String^ text);
		IAsyncAction^ runInputStringAsync();
		IAsyncAction^ runDefaultGameAsync();

		IAsyncAction^ execLinkAsync(Platform::String^ text);
	};
}
