#include "pch.h"
#include "UwpJsExecutor.h"

using namespace Windows::UI::Core;

namespace QspLibWinRT {
	UwpJsExecutor::UwpJsExecutor()
	{
	}

	bool UwpJsExecutor::jsCallApi(Platform::String^ name, Platform::String^ message)
	{
		this->getDispatcher()->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, name, message]()
		{
			this->callApiEvent(name, message);
		}, Platform::CallbackContext::Any));

		return true;
	}

	bool UwpJsExecutor::jsCallDebug(Platform::String^ message)
	{
		// Since this code is probably running on a worker
		// thread, and we are passing the data back to the
		// UI thread, we have to use a CoreDispatcher object.
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

