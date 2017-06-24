#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"

using namespace QuestNavigator;

namespace QspLibWinRT
{
	// Делегаты для обработки событий в JS.
	public delegate void CallSetGroupedContentHandler(Platform::String^ groupedContent);
	public delegate void CallShowSaveSlotsDialogHandler(Platform::String^ saveSlots);
	public delegate void CallMsgHandler(Platform::String^ text);
	public delegate void CallErrorHandler(Platform::String^ error);

	public delegate void ShowDebugMessageHandler(Platform::String^ testMessage);

	// Объект для вызова JS-кода из C++.
	public ref class UwpJsExecutor sealed
	{
	public:
		UwpJsExecutor();

		void jsCallSetGroupedContent(Platform::String^ groupedContent);
		void jsCallShowSaveSlotsDialog(Platform::String^ saveSlots);
		void jsCallMsg(Platform::String^ text);
		void jsCallError(Platform::String^ error);

		// Для тестирования колбеков.
		void jsCallDebug(Platform::String^ message);

		// Событие-делегат для запуска JS-кода из C++.
		// В JS скрипте к этому событию привязывается обработчик.
		event CallSetGroupedContentHandler^ callSetGroupedContentEvent;
		event CallShowSaveSlotsDialogHandler^ callShowSaveSlotsDialogEvent;
		event CallMsgHandler^ callMsgEvent;
		event CallErrorHandler^ callErrorEvent;

		event ShowDebugMessageHandler^ showDebugMessageEvent;

	private:
		Windows::UI::Core::CoreDispatcher^ getDispatcher();
	};
}

