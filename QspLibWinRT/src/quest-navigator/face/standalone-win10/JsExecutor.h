#pragma once

#include <string>
#include <vector>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "..\..\core\dto\ErrorDto.h"
#include "..\..\platform\windows10\UwpJsExecutor.h"
#include "..\..\platform\windows10\StringConverter.h"
#include "JsonSerializer.h"

using namespace std;
using namespace QspLibWinRT;

namespace QuestNavigator
{
	class JsExecutor
	{
	public:
		JsExecutor();
		~JsExecutor();

		void inject(
			UwpJsExecutor^ uwpJsExecutor,
			StringConverter* stringConverter,
			JsonSerializer* jsonSerializer
		);

		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		//                        Вызовы JS-функций
		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		
		// В потоке Ui
		//		void processLibJsCall();
		//		bool onWebDeviceReady();
		void qspShowSaveSlotsDialog(SaveSlotsDto slotsDto);
		//		void qspFillLocalGamesList(JSArray games);

		// В потоке библиотеки
		//		static void jsCallApiFromLib(string name, JSValue arg);
		void qspSetGroupedContent(GroupedContentDto content);
		void qspMsg(string text);
		void qspError(ErrorDto error);
		void qspMenu(vector<MenuItemDto> menu);
		void qspInput(string text);
		void qspView(string path);
		void qspSetInputString(string text);

	private:
		UwpJsExecutor^ uwpJsExecutor;
		StringConverter* stringConverter;
		JsonSerializer* jsonSerializer;

		// В потоке Ui
		bool jsCallApi(string name, string arg);
		bool jsCallDebug(string message);
	};
}