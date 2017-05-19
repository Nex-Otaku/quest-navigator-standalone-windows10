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
		//                        ������ JS-�������
		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		
		// � ������ Ui
		//		void processLibJsCall();
		//		bool jsCallApiFromUi(string name, JSValue arg);
		//		bool onWebDeviceReady();
		void qspShowSaveSlotsDialog(SaveSlotsDto slotsDto);
		//		void qspFillLocalGamesList(JSArray games);

		// � ������ ����������
		//		static void jsCallApiFromLib(string name, JSValue arg);
		static void qspSetGroupedContent(GroupedContentDto content);
		static void qspMsg(string text);
		//		static void qspError(JSObject error);
		//		static void qspMenu(JSArray menu);
		static void qspInput(string text);
		static void qspView(string path);
		static void qspSetInputString(string text);
	};
}