#pragma once

#include "dto\SaveSlotsDto.h"

namespace QuestNavigator
{
	class JsExecutor
	{
	public:
		JsExecutor();
		~JsExecutor();

		void qspShowSaveSlotsDialog(SaveSlotsDto slotsDto);


	};
	//		// ********************************************************************
	//		// ********************************************************************
	//		// ********************************************************************
	//		//                        Вызовы JS-функций
	//		// ********************************************************************
	//		// ********************************************************************
	//		// ********************************************************************
	//
	//		// В потоке Ui
	//		void processLibJsCall();
	//		bool jsCallApiFromUi(string name, JSValue arg);
	//		bool onWebDeviceReady();
	//		void qspShowSaveSlotsDialog(JSObject content);
	//		void qspFillLocalGamesList(JSArray games);
	//
	//		// В потоке библиотеки
	//		static void jsCallApiFromLib(string name, JSValue arg);
	//		static void qspSetGroupedContent(JSObject content);
	//		static void qspMsg(WebString text);
	//		static void qspError(JSObject error);
	//		static void qspMenu(JSArray menu);
	//		static void qspInput(WebString text);
	//		static void qspView(WebString path);
	//		static void qspSetInputString(WebString text);
}