#include "pch.h"
#include "UwpJsExecutor.h"

//using namespace concurrency;
//using namespace Platform::Collections;
//using namespace Windows::Foundation::Collections;
//using namespace Windows::Foundation;
using namespace Windows::UI::Core;

namespace QspLibWinRT {
	UwpJsExecutor::UwpJsExecutor()
	{
	}

	bool UwpJsExecutor::jsCallApiFromUi(Platform::String^ name, Platform::String^ message /* slotsDto */)
	{
		auto window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
		Windows::UI::Core::CoreDispatcher^ m_dispatcher;
		m_dispatcher = window->Dispatcher;

		// Since this code is probably running on a worker
		// thread, and we are passing the data back to the
		// UI thread, we have to use a CoreDispatcher object.
		m_dispatcher->RunAsync(CoreDispatcherPriority::Normal,
			ref new DispatchedHandler([this, message/* slotsDto */]()
		{
			// Потом мы здесь передадим структуру для вызова слотов сохранения.
			this->showSaveSlotsDialogEvent("testMessage");

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
			this->showDebugMessageEvent("testMessage");

		}, Platform::CallbackContext::Any));

		return true;
	}

	Windows::UI::Core::CoreDispatcher^ UwpJsExecutor::getDispatcher()
	{
		auto window = Windows::UI::Core::CoreWindow::GetForCurrentThread();
		return window->Dispatcher;
	}
}

