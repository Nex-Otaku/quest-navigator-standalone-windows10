#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"

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
		//		static void qspMsg(WebString text);
		//		static void qspError(JSObject error);
		//		static void qspMenu(JSArray menu);
		//		static void qspInput(WebString text);
		//		static void qspView(WebString path);
		static void qspSetInputString(string text);
	};
}