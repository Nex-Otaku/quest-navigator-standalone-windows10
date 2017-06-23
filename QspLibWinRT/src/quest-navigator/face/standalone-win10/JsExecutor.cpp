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

	void JsExecutor::inject(UwpJsExecutor^ uwpJsExecutor, StringConverter* stringConverter)
	{
		this->uwpJsExecutor = uwpJsExecutor;
		this->stringConverter = stringConverter;
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
		// Контекст UI
		//jsCallApiFromUi("qspShowSaveSlotsDialog", slotsDto);

		jsCallDebug("qspShowSaveSlotsDialog");
	}

	void JsExecutor::qspSetGroupedContent(GroupedContentDto content)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspSetGroupedContent", content);
		jsCallDebug("qspSetGroupedContent");
	}

	void JsExecutor::qspMsg(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspMsg", text);
		jsCallDebug("qspMsg");
	}

	void JsExecutor::qspError(ErrorDto error)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspError", error);
		jsCallDebug("qspError");
	}

	void JsExecutor::qspMenu(vector<MenuItemDto> menu)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspMenu", menu);
		jsCallDebug("qspMenu");
	}

	void JsExecutor::qspInput(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspInput", text);
		jsCallDebug("qspInput");
	}

	void JsExecutor::qspView(string path)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspView", path);
		jsCallDebug("qspView");
	}

	void JsExecutor::qspSetInputString(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspSetInputString", text);
		jsCallDebug("qspSetInputString");
	}

	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	//                        Инфраструктура
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************

	bool JsExecutor::jsCallApiFromUi(string name, SaveSlotsDto slotsDto)
	{
		// Контекст UI

		Platform::String^ pName = stringConverter->convertStdToUwp(name);
		Platform::String^ pMessage = stringConverter->convertStdToUwp("test");

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
		//		showError("Ошибка при выполнении JS-вызова.");
		//		return false;
		//	}
		//} else {
		//	showError("Не удалось получить доступ к объекту окна.");
		//	return false;
		//}
		//return true;

		// STUB
		return true;
	}

	bool JsExecutor::jsCallDebug(string message)
	{
		// Контекст UI
		Platform::String^ pMessage = stringConverter->convertStdToUwp(message);

		return uwpJsExecutor->jsCallDebug(pMessage);
	}
}