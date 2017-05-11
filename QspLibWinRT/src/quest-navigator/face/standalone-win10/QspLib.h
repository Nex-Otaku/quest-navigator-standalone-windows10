#pragma once

#include "JsListener.h"

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

	private:
		JsListener* jsListener;
	};
}

//	// Контейнер для элемента меню
//	struct ContainerMenuItem {
//		string imgPath;
//		string name;
//	};
//
//
//	class QnApplicationListener : public Application::Listener, public Awesomium::WebViewListener::Load {
//		Application* app_;
//		View* view_;
//		DataSource* data_source_;
//		MethodDispatcher method_dispatcher_;
//		QnInterceptor resource_interceptor_;
//
//		bool gameIsRunning;
//		bool programLoaded;
//		bool jsLibObjectCreated;
//
//		HANDLE libThread;
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
//		// ********************************************************************
//		// ********************************************************************
//		// ********************************************************************
//		//                       Колбэки интерпретатора
//		// ********************************************************************
//		// ********************************************************************
//		// ********************************************************************
//
//		static void RefreshInt(int isRedraw);
//		static void SetTimer(int msecs);
//		static void SetInputStrText(QSP_CHAR* text);
//		static void ShowMessage(QSP_CHAR* message);
//		static void PlayFile(QSP_CHAR* file, int volume);
//		static QSP_BOOL IsPlayingFile(QSP_CHAR* file);
//		static void CloseFile(QSP_CHAR* file);
//		static void ShowPicture(QSP_CHAR* file);
//		static void InputBox(const QSP_CHAR* prompt, QSP_CHAR* buffer, int maxLen);
//		static void PlayerInfo(QSP_CHAR* resource, QSP_CHAR* buffer, int maxLen);
//		static int GetMSCount();
//		static void AddMenuItem(QSP_CHAR* name, QSP_CHAR* imgPath);
//		static int ShowMenu();
//		static void DeleteMenu();
//		static void Wait(int msecs);
//		static void ShowWindow(int type, QSP_BOOL isShow);
//		static void System(QSP_CHAR* cmd);
//		static void OpenGameStatus(QSP_CHAR* file);
//		static void SaveGameStatus(QSP_CHAR* file);
//
//		// ********************************************************************
//		// ********************************************************************
//		// ********************************************************************
//		//                        Вызовы JS-функций
//		// ********************************************************************
//		// ********************************************************************
//		// ********************************************************************
//
//		// В потоке Ui
//		void processLibJsCall();
//		bool jsCallApiFromUi(string name, JSValue arg);
//		bool onWebDeviceReady();
//		void qspShowSaveSlotsDialog(JSObject content);
//		void qspFillLocalGamesList(JSArray games);
//
//		// В потоке библиотеки
//		static void jsCallApiFromLib(string name, JSValue arg);
//		static void qspSetGroupedContent(JSObject content);
//		static void qspMsg(WebString text);
//		static void qspError(JSObject error);
//		static void qspMenu(JSArray menu);
//		static void qspInput(WebString text);
//		static void qspView(WebString path);
//		static void qspSetInputString(WebString text);
//
//
//		// ********************************************************************
//		// Вспомогательные обработчики для отладки
//		// ********************************************************************
//		void alert(WebView* caller, const JSArray& args);
//
//		// ********************************************************************
//		// Переменные библиотеки
//		// ********************************************************************
//
//		static string jsExecBuffer;
//		static string lastMainDesc;
//		static QnApplicationListener* listener;
//		static vector<ContainerMenuItem> menuList;
//		static clock_t gameStartTime;
//		static int timerInterval;
//
//		static int objectSelectionIndex;
//
//		// ********************************************************************
//		// THREADS
//		// ********************************************************************
//
//		// Запуск потока библиотеки
//		void StartLibThread();
//		// Остановка потока библиотеки
//		void StopLibThread();
//		// Основная функция потока библиотеки
//		static unsigned int __stdcall libThreadFunc(void* pvParam);
//
//		// Проверка результатов выполнения библиотечного кода
//		static void CheckQspResult(QSP_BOOL successfull, string failMsg);
//		// Установка и запуск таймера
//		static void startTimer();
//		// Остановка таймера
//		static void stopTimer();
//	};
