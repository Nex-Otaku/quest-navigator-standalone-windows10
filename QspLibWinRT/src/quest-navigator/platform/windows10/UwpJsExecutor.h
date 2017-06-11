#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"

using namespace std;
using namespace QuestNavigator;

namespace QspLibWinRT
{
	// �������� ��� ��������� ������� � JS.
	// ��� �������� � ������� JS ���������?
	public delegate void ShowSaveSlotsDialogHandler(Platform::String^ testMessage);


	public delegate void ShowDebugMessageHandler(Platform::String^ testMessage);

	// ������ ��� ������ JS-���� �� C++.
	public ref class UwpJsExecutor sealed
	{
	public:
		UwpJsExecutor();

		// � ������ Ui
		// bool jsCallApiFromUi(Platform::String^ name, SaveSlotsDto slotsDto);
		bool jsCallApiFromUi(Platform::String^ name, Platform::String^ message);

		// ��� ������������ ��������.
		bool jsCallDebug(Platform::String^ message);

		event ShowDebugMessageHandler^ showDebugMessageEvent;

	private:
		// ������� ��� ������� JS-���� �� C++.
		// Event whose type is a delegate "class"
		event ShowSaveSlotsDialogHandler^ showSaveSlotsDialogEvent;


		Windows::UI::Core::CoreDispatcher^ getDispatcher();
	};
}

