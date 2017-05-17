#include "pch.h"
#include "JsExecutor.h"

namespace QuestNavigator
{
	JsExecutor::JsExecutor()
	{
	}

	JsExecutor::~JsExecutor()
	{
	}

	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	//                        Вызовы JS-функций
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************

	void JsExecutor::qspShowSaveSlotsDialog(SaveSlotsDto slotsDto)
	{
		//		// Контекст UI
		//		jsCallApiFromUi("qspShowSaveSlotsDialog", content);
	}

	void JsExecutor::qspSetGroupedContent(GroupedContentDto content)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspSetGroupedContent", content);
	}

	void JsExecutor::qspSetInputString(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspSetInputString", text);
	}
}