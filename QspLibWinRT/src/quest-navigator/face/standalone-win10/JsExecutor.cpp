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
		//jsCallApiFromUi("qspShowSaveSlotsDialog", slotsDto);

		jsCallDebug("qspShowSaveSlotsDialog stub");
	}

	void JsExecutor::qspSetGroupedContent(GroupedContentDto content)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspSetGroupedContent", content);
		//jsCallDebug("qspSetGroupedContent");

		//JsonObject^ jsonObject = ref new JsonObject();

		//jsonObject->Insert()


		string jsonGroupedContentDto = jsonSerializer->serializeGroupedContent(content);

		Platform::String^ pGroupedContent = stringConverter->convertStdToUwp(jsonGroupedContentDto);

		uwpJsExecutor->jsCallSetGroupedContent(pGroupedContent);


		//MemoryStream stream = new MemoryStream();
		//DataContractJsonSerializer jsonSer = new DataContractJsonSerializer(typeof(Student));
		//jsonSer.WriteObject(stream, objStudent);
		//stream.Position = 0;
		//StreamReader sr = new StreamReader(stream);
		//lblSerilaize.Text = sr.ReadToEnd();

		//string jsonContent = (new Windows::Data::Json::JsonObject())->
		//jsCallApi("qspSetGroupedContent", content);
		//jsCallApi("qspSetGroupedContent", jsonGroupedContentDto);
	}

	void JsExecutor::qspMsg(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspMsg", text);
		jsCallDebug("qspMsg stub");
	}

	void JsExecutor::qspError(ErrorDto error)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspError", error);
		jsCallDebug("qspError stub");
	}

	void JsExecutor::qspMenu(vector<MenuItemDto> menu)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspMenu", menu);
		jsCallDebug("qspMenu stub");
	}

	void JsExecutor::qspInput(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspInput", text);
		jsCallDebug("qspInput stub");
	}

	void JsExecutor::qspView(string path)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspView", path);
		jsCallDebug("qspView stub");
	}

	void JsExecutor::qspSetInputString(string text)
	{
		//		// Контекст библиотеки
		//		jsCallApiFromLib("qspSetInputString", text);
		jsCallDebug("qspSetInputString stub");
	}

	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	//                        Инфраструктура
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************

	//bool JsExecutor::jsCallApi(string name, string arg)
	//{
	//	Platform::String^ pName = stringConverter->convertStdToUwp(name);
	//	Platform::String^ pArg = stringConverter->convertStdToUwp(arg);

	//	return uwpJsExecutor->jsCallApi(pName, pArg);
	//}

	bool JsExecutor::jsCallDebug(string message)
	{
		// Контекст UI
		Platform::String^ pMessage = stringConverter->convertStdToUwp(message);

		return uwpJsExecutor->jsCallDebug(pMessage);
	}
}