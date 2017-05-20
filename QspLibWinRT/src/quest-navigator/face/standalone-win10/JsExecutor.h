#pragma once

#include <string>
#include <vector>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "..\..\core\dto\ErrorDto.h"

using namespace std;

namespace QuestNavigator
{
	class JsExecutor
	{
	public:
		JsExecutor();
		~JsExecutor();

		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		//                        Вызовы JS-функций
		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		
		// В потоке Ui
		//		void processLibJsCall();
		//		bool jsCallApiFromUi(string name, JSValue arg);
		//		bool onWebDeviceReady();
		void qspShowSaveSlotsDialog(SaveSlotsDto slotsDto);
		//		void qspFillLocalGamesList(JSArray games);

		// В потоке библиотеки
		//		static void jsCallApiFromLib(string name, JSValue arg);
		static void qspSetGroupedContent(GroupedContentDto content);
		static void qspMsg(string text);
		static void qspError(ErrorDto error);
		static void qspMenu(vector<MenuItemDto> menu);
		static void qspInput(string text);
		static void qspView(string path);
		static void qspSetInputString(string text);
	};
}