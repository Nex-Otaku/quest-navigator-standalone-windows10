#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"

using namespace std;
using namespace QuestNavigator;

namespace QspLibWinRT
{
	// Делегаты для обработки событий в JS.
	// Как передать в делегат JS структуру?
	public delegate void ShowSaveSlotsDialogHandler(Platform::String^ testMessage);


	public delegate void ShowDebugMessageHandler(Platform::String^ testMessage);

	// Объект для вызова JS-кода из C++.
	public ref class UwpJsExecutor sealed
	{
	public:
		UwpJsExecutor();

		// В потоке Ui
		// bool jsCallApiFromUi(Platform::String^ name, SaveSlotsDto slotsDto);
		bool jsCallApiFromUi(Platform::String^ name, Platform::String^ message);

		// Для тестирования колбеков.
		bool jsCallDebug(Platform::String^ message);

		event ShowDebugMessageHandler^ showDebugMessageEvent;

	private:
		// Делегат для запуска JS-кода из C++.
		// Event whose type is a delegate "class"
		event ShowSaveSlotsDialogHandler^ showSaveSlotsDialogEvent;


		Windows::UI::Core::CoreDispatcher^ getDispatcher();
	};
}

