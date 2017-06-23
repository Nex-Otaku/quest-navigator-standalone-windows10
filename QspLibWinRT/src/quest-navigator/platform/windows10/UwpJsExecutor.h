#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"

using namespace QuestNavigator;

namespace QspLibWinRT
{
	// Делегаты для обработки событий в JS.
	public delegate void CallApiHandler(Platform::String^ name, Platform::String^ message);
	public delegate void ShowDebugMessageHandler(Platform::String^ testMessage);

	// Объект для вызова JS-кода из C++.
	public ref class UwpJsExecutor sealed
	{
	public:
		UwpJsExecutor();

		// В потоке Ui
		//bool jsCallApiFromUi(Platform::String^ name, SaveSlotsDto slotsDto);
		bool jsCallApi(Platform::String^ name, Platform::String^ message);

		// Для тестирования колбеков.
		bool jsCallDebug(Platform::String^ message);

		event ShowDebugMessageHandler^ showDebugMessageEvent;

	private:
		// Делегат для запуска JS-кода из C++.
		// Event whose type is a delegate "class"
		event CallApiHandler^ callApiEvent;

		Windows::UI::Core::CoreDispatcher^ getDispatcher();
	};
}

