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
	//                        ������ JS-�������
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************

	void JsExecutor::qspShowSaveSlotsDialog(SaveSlotsDto slotsDto)
	{
		//		// �������� UI
		//		jsCallApiFromUi("qspShowSaveSlotsDialog", content);
	}

	void JsExecutor::qspSetGroupedContent(GroupedContentDto content)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspSetGroupedContent", content);
	}

	void JsExecutor::qspMsg(string text)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspMsg", text);
	}

	void JsExecutor::qspError(ErrorDto error)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspError", error);
	}

	void JsExecutor::qspMenu(vector<MenuItemDto> menu)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspMenu", menu);
	}

	void JsExecutor::qspInput(string text)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspInput", text);
	}

	void JsExecutor::qspView(string path)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspView", path);
	}

	void JsExecutor::qspSetInputString(string text)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspSetInputString", text);
	}
}