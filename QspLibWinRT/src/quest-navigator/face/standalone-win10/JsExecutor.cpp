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

	void JsExecutor::qspMsg(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspMsg", text);
	}

	void JsExecutor::qspError(ErrorDto error)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspError", error);
	}

	void JsExecutor::qspMenu(vector<MenuItemDto> menu)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspMenu", menu);
	}

	void JsExecutor::qspInput(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspInput", text);
	}

	void JsExecutor::qspView(string path)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspView", path);
	}

	void JsExecutor::qspSetInputString(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspSetInputString", text);
	}
}