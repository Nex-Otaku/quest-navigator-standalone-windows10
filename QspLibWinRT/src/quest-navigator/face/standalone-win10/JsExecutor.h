#pragma once

#include <string>
#include <vector>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "..\..\core\dto\ErrorDto.h"
#include "..\..\platform\windows10\UwpJsExecutor.h"
#include "..\..\platform\windows10\StringConverter.h"
#include "JsonSerializer.h"

using namespace std;
using namespace QspLibWinRT;

namespace QuestNavigator
{
	class JsExecutor
	{
	public:
		JsExecutor();
		~JsExecutor();

		void inject(
			UwpJsExecutor^ uwpJsExecutor,
			StringConverter* stringConverter,
			JsonSerializer* jsonSerializer
		);

		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		//                        Вызовы JS-функций
		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		
		// В потоке Ui
		void qspShowSaveSlotsDialog(SaveSlotsDto slotsDto);

		// В потоке библиотеки
		void qspSetGroupedContent(GroupedContentDto content);
		void qspMsg(string text);
		void qspError(ErrorDto error);
		void qspMenu(vector<MenuItemDto> menu);
		void qspInput(string text);
		void qspView(string path);
		void qspSetInputString(string text);

		// Поток библиотеки запущен и готов к обработке команд.
		void qspLibraryInited();

	private:
		UwpJsExecutor^ uwpJsExecutor;
		StringConverter* stringConverter;
		JsonSerializer* jsonSerializer;

		void jsCallDebug(string message);
	};
}