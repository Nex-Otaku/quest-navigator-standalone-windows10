#pragma once

#include <string>
#include <vector>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "..\..\core\dto\ErrorDto.h"
#include "..\..\platform\windows10\UwpJsExecutor.h"

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
			UwpJsExecutor^ uwpJsExecutor
		);

		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		//                        ������ JS-�������
		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		
		// � ������ Ui
		//		void processLibJsCall();
		//		bool onWebDeviceReady();
		void qspShowSaveSlotsDialog(SaveSlotsDto slotsDto);
		//		void qspFillLocalGamesList(JSArray games);

		// � ������ ����������
		//		static void jsCallApiFromLib(string name, JSValue arg);
		void qspSetGroupedContent(GroupedContentDto content);
		void qspMsg(string text);
		void qspError(ErrorDto error);
		void qspMenu(vector<MenuItemDto> menu);
		void qspInput(string text);
		void qspView(string path);
		void qspSetInputString(string text);

	private:
		UwpJsExecutor^ uwpJsExecutor;

		// � ������ Ui
		bool jsCallApiFromUi(string name, SaveSlotsDto slotsDto);
		bool jsCallDebug(string message);

		// ����������� �����
		Platform::String^ convertFromString(string input);
	};
}