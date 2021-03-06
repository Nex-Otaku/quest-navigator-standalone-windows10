#include "pch.h"
#include "UwpJsExecutor.h"

using namespace Windows::UI::Core;

namespace QspLibWinRT {
	UwpJsExecutor::UwpJsExecutor()
	{
	}

	void UwpJsExecutor::jsCallSetGroupedContent(Platform::String^ groupedContent)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, groupedContent]()
		{
			this->callSetGroupedContentEvent(groupedContent);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallShowSaveSlotsDialog(Platform::String^ saveSlots)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, saveSlots]()
		{
			this->callShowSaveSlotsDialogEvent(saveSlots);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallMsg(Platform::String^ text)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, text]()
		{
			this->callMsgEvent(text);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallError(Platform::String^ error)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, error]()
		{
			this->callErrorEvent(error);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallMenu(Platform::String^ menu)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, menu]()
		{
			this->callMenuEvent(menu);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallInput(Platform::String^ text)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, text]()
		{
			this->callInputEvent(text);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallView(Platform::String^ path)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, path]()
		{
			this->callViewEvent(path);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallSetInputString(Platform::String^ text)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, text]()
		{
			this->callSetInputStringEvent(text);
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallLibraryInited()
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this]()
		{
			this->callLibraryInitedEvent();
		}, Platform::CallbackContext::Any));
	}

	void UwpJsExecutor::jsCallDebug(Platform::String^ message)
	{
		getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, message]()
		{
			// Просто передаём тестовое сообщение.
			this->showDebugMessageEvent(message);
		}, Platform::CallbackContext::Any));
	}

	Windows::UI::Core::CoreDispatcher^ UwpJsExecutor::getDispatcher()
	{
		return Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher;
	}
}

