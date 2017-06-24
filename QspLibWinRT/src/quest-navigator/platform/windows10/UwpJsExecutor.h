#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"

using namespace QuestNavigator;

namespace QspLibWinRT
{
	// Делегаты для обработки событий в JS.
	public delegate void CallSetGroupedContentHandler(Platform::String^ groupedContent);
	public delegate void CallShowSaveSlotsDialog(Platform::String^ saveSlots);

	public delegate void ShowDebugMessageHandler(Platform::String^ testMessage);

	// Объект для вызова JS-кода из C++.
	public ref class UwpJsExecutor sealed
	{
	public:
		UwpJsExecutor();

		bool jsCallSetGroupedContent(Platform::String^ groupedContent);
		bool jsCallShowSaveSlotsDialog(Platform::String^ saveSlots);

		// Для тестирования колбеков.
		bool jsCallDebug(Platform::String^ message);

		// Событие-делегат для запуска JS-кода из C++.
		// В JS скрипте к этому событию привязывается обработчик.
		event CallSetGroupedContentHandler^ callSetGroupedContentEvent;
		event CallSetGroupedContentHandler^ callShowSaveSlotsDialogEvent;

		event ShowDebugMessageHandler^ showDebugMessageEvent;

	private:
		Windows::UI::Core::CoreDispatcher^ getDispatcher();
	};
}

