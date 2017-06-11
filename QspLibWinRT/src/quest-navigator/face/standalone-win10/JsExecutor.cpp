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

	void JsExecutor::inject(UwpJsExecutor ^ uwpJsExecutor)
	{
		this->uwpJsExecutor = uwpJsExecutor;
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
		// �������� UI
		//jsCallApiFromUi("qspShowSaveSlotsDialog", slotsDto);

		jsCallDebug("qspShowSaveSlotsDialog");
	}

	void JsExecutor::qspSetGroupedContent(GroupedContentDto content)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspSetGroupedContent", content);
		jsCallDebug("qspSetGroupedContent");
	}

	void JsExecutor::qspMsg(string text)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspMsg", text);
		jsCallDebug("qspMsg");
	}

	void JsExecutor::qspError(ErrorDto error)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspError", error);
		jsCallDebug("qspError");
	}

	void JsExecutor::qspMenu(vector<MenuItemDto> menu)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspMenu", menu);
		jsCallDebug("qspMenu");
	}

	void JsExecutor::qspInput(string text)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspInput", text);
		jsCallDebug("qspInput");
	}

	void JsExecutor::qspView(string path)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspView", path);
		jsCallDebug("qspView");
	}

	void JsExecutor::qspSetInputString(string text)
	{
		//		// �������� ����������
		//		jsCallApiFromLib("qspSetInputString", text);
		jsCallDebug("qspSetInputString");
	}

	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	//                        ��������������
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************

	bool JsExecutor::jsCallApiFromUi(string name, SaveSlotsDto slotsDto)
	{
		// �������� UI

		Platform::String^ pName = convertFromString(name);
		Platform::String^ pMessage = convertFromString("test");


		return uwpJsExecutor->jsCallApiFromUi(pName, pMessage /* slotsDto */);




		//JSValue window = view_->web_view()->ExecuteJavascriptWithResult(
		//	WSLit("window"), WSLit(""));
		//if (window.IsObject()) {
		//	JSArray args;
		//	args.Push(arg);
		//	JSObject windowObject = window.ToObject();
		//	windowObject.Invoke(ToWebString(name), args);
		//	Error err = windowObject.last_error();
		//	if (err != Error::kError_None) {
		//		showError("������ ��� ���������� JS-������.");
		//		return false;
		//	}
		//} else {
		//	showError("�� ������� �������� ������ � ������� ����.");
		//	return false;
		//}
		//return true;

		// STUB
		return true;
	}

	bool JsExecutor::jsCallDebug(string message)
	{
		// �������� UI

		Platform::String^ pMessage = convertFromString("test");

		return uwpJsExecutor->jsCallDebug(pMessage);
	}

	Platform::String^ JsExecutor::convertFromString(string input)
	{
		std::wstring w_str = std::wstring(input.begin(), input.end());
		const wchar_t* w_chars = w_str.c_str();

		return (ref new Platform::String(w_chars));
	}
}