#include "pch.h"
#include "JsExecutor.h"
#include "..\..\platform\windows10\StringConverter.h"
#include "JsonSerializer.h"

namespace QuestNavigator
{
	JsExecutor::JsExecutor()
	{
	}

	JsExecutor::~JsExecutor()
	{
	}

	void JsExecutor::inject(
		UwpJsExecutor^ uwpJsExecutor, 
		StringConverter* stringConverter,
		JsonSerializer* jsonSerializer
	)
	{
		this->uwpJsExecutor = uwpJsExecutor;
		this->stringConverter = stringConverter;
		this->jsonSerializer = jsonSerializer;
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
		//jsCallDebug("qspShowSaveSlotsDialog stub");
		string jsonSaveSlotsDto = jsonSerializer->serializeSaveSlots(slotsDto);
		Platform::String^ pSaveSlots = stringConverter->convertStdToUwp(jsonSaveSlotsDto);
		uwpJsExecutor->jsCallShowSaveSlotsDialog(pSaveSlots);
	}

	void JsExecutor::qspSetGroupedContent(GroupedContentDto content)
	{
		string jsonGroupedContentDto = jsonSerializer->serializeGroupedContent(content);
		Platform::String^ pGroupedContent = stringConverter->convertStdToUwp(jsonGroupedContentDto);
		uwpJsExecutor->jsCallSetGroupedContent(pGroupedContent);
	}

	void JsExecutor::qspMsg(string text)
	{
		// Контекст библиотеки
		//jsCallDebug("qspMsg stub");
		Platform::String^ pText = stringConverter->convertStdToUwp(text);
		uwpJsExecutor->jsCallMsg(pText);
	}

	void JsExecutor::qspError(ErrorDto error)
	{
		// Контекст библиотеки
		//jsCallDebug("qspError stub");
		string jsonErrorDto = jsonSerializer->serializeError(error);
		Platform::String^ pError = stringConverter->convertStdToUwp(jsonErrorDto);
		uwpJsExecutor->jsCallError(pError);
	}

	void JsExecutor::qspMenu(vector<MenuItemDto> menu)
	{
		// Контекст библиотеки
		//jsCallDebug("qspMenu stub");
		string jsonMenuDto = jsonSerializer->serializeMenu(menu);
		Platform::String^ pMenu = stringConverter->convertStdToUwp(jsonMenuDto);
		uwpJsExecutor->jsCallMenu(pMenu);
	}

	void JsExecutor::qspInput(string text)
	{
		// Контекст библиотеки
		//jsCallDebug("qspInput stub");
		Platform::String^ pText = stringConverter->convertStdToUwp(text);
		uwpJsExecutor->jsCallInput(pText);
	}

	void JsExecutor::qspView(string path)
	{
		// Контекст библиотеки
		//jsCallDebug("qspView stub");
		Platform::String^ pPath = stringConverter->convertStdToUwp(path);
		uwpJsExecutor->jsCallView(pPath);
	}

	void JsExecutor::qspSetInputString(string text)
	{
		// Контекст библиотеки
		//jsCallDebug("qspSetInputString stub");
		Platform::String^ pText = stringConverter->convertStdToUwp(text);
		uwpJsExecutor->jsCallSetInputString(pText);
	}

	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	//                        Инфраструктура
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************

	void JsExecutor::jsCallDebug(string message)
	{
		// Контекст UI
		Platform::String^ pMessage = stringConverter->convertStdToUwp(message);

		uwpJsExecutor->jsCallDebug(pMessage);
	}
}