#pragma once

#include "JsListener.h"
#include "..\..\platform\windows10\UwpJsExecutor.h"

using namespace QuestNavigator;

namespace QspLibWinRT
{
	public ref class QspLib sealed
	{
	public:
		QspLib();

		void restartGame();
		void executeAction(int32 pos);
		void selectObject(int32 pos);
		void loadGame();
		void saveGame();
		void saveSlotSelected(int32 index, int32 mode);
		void msgResult();
		void errorResult();
		void userMenuResult(int32 pos);
		void inputResult(Platform::String^ text);
		void setMute(Platform::Boolean flag);
		void setInputString(Platform::String^ text);
		void runInputString();
		void runDefaultGame();

		// Метод для отладки
		void callDebugMessage();

		// Объект для привязки колбеков.
		UwpJsExecutor^ getUwpJsExecutor();
	private:
		JsListener* jsListener;
		UwpJsExecutor^ uwpJsExecutor;
	};
}

//	class QnApplicationListener : public Application::Listener, public Awesomium::WebViewListener::Load {
//		Application* app_;
//		View* view_;
//		DataSource* data_source_;
//		MethodDispatcher method_dispatcher_;
//		QnInterceptor resource_interceptor_;
//
//		bool programLoaded;
//		bool jsLibObjectCreated;
//
//		// Хэндл мьютекса.
//		HANDLE hInstanceMutex;
//
//	public:
//		QnApplicationListener();
//		virtual ~QnApplicationListener();
//
//		void Run();
//
//		// Inherited from Application::Listener
//		virtual void OnLoaded();
//		virtual void OnUpdate();
//		virtual void OnShutdown();
//
//		// ********************************************************************
//		// Inherited from WebViewListener::Load
//		// ********************************************************************
//		/// This event occurs when the page begins loading a frame.
//		virtual void OnBeginLoadingFrame(Awesomium::WebView* caller,
//			int64 frame_id,
//			bool is_main_frame,
//			const Awesomium::WebURL& url,
//			bool is_error_page);
//		/// This event occurs when a frame fails to load. See error_desc
//		/// for additional information.
//		virtual void OnFailLoadingFrame(Awesomium::WebView* caller,
//			int64 frame_id,
//			bool is_main_frame,
//			const Awesomium::WebURL& url,
//			int error_code,
//			const Awesomium::WebString& error_desc);
//		/// This event occurs when the page finishes loading a frame.
//		/// The main frame always finishes loading last for a given page load.
//		virtual void OnFinishLoadingFrame(Awesomium::WebView* caller,
//			int64 frame_id,
//			bool is_main_frame,
//			const Awesomium::WebURL& url);
//		/// This event occurs when the DOM has finished parsing and the
//		/// window object is available for JavaScript execution.
//		virtual void OnDocumentReady(Awesomium::WebView* caller,
//			const Awesomium::WebURL& url);
//		// ********************************************************************
//
//		bool BindMethods(WebView* web_view);
//
//
//		// ********************************************************************
//		// Вспомогательные обработчики для отладки
//		// ********************************************************************
//		void alert(WebView* caller, const JSArray& args);
//
//	};
