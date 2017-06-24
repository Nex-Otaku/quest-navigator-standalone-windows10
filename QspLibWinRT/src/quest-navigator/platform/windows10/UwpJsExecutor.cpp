#include "pch.h"
#include "UwpJsExecutor.h"

using namespace Windows::UI::Core;

namespace QspLibWinRT {
	UwpJsExecutor::UwpJsExecutor()
	{
	}

	bool UwpJsExecutor::jsCallSetGroupedContent(Platform::String^ groupedContent)
	{
		this->getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, groupedContent]()
		{
			this->callSetGroupedContentEvent(groupedContent);
		}, Platform::CallbackContext::Any));

		return true;
	}

	bool UwpJsExecutor::jsCallShowSaveSlotsDialog(Platform::String^ saveSlots)
	{
		this->getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, saveSlots]()
		{
			this->callShowSaveSlotsDialogEvent(saveSlots);
		}, Platform::CallbackContext::Any));

		return true;
	}

	bool UwpJsExecutor::jsCallDebug(Platform::String^ message)
	{
		this->getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, message]()
		{
			// Просто передаём тестовое сообщение.
			this->showDebugMessageEvent(message);
		}, Platform::CallbackContext::Any));

		return true;
	}

	Windows::UI::Core::CoreDispatcher^ UwpJsExecutor::getDispatcher()
	{
		return Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher;
	}
}

