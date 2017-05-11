#pragma once

//#include "../common/application.h"
//#include "../common/view.h"
//#include "../common/method_dispatcher.h"
//#include "../deps/qsp/qsp.h"
//#include "../deps/qsp/bindings/default/qsp_default.h"
//#include <Awesomium/WebCore.h>
//#include <Awesomium/DataPak.h>
//#include <Awesomium/STLHelpers.h>
//#include "utils.h"
//#include "interceptor.h"
//#include <vector>
//#include <time.h>
//
//using namespace Awesomium;
//
//namespace QuestNavigator {
//
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
//		// ********************************************************************
//		// ********************************************************************
//		// ********************************************************************
//		//                   Обработчики вызовов из JS
//		// ********************************************************************
//		// ********************************************************************
//		// ********************************************************************
//
//		void restartGame(WebView* caller, const JSArray& args);
//		void executeAction(WebView* caller, const JSArray& args);
//		void selectObject(WebView* caller, const JSArray& args);
//		void loadGame(WebView* caller, const JSArray& args);
//		void saveGame(WebView* caller, const JSArray& args);
//		void saveSlotSelected(WebView* caller, const JSArray& args);
//		void msgResult(WebView* caller, const JSArray& args);
//		void errorResult(WebView* caller, const JSArray& args);
//		void userMenuResult(WebView* caller, const JSArray& args);
//		void inputResult(WebView* caller, const JSArray& args);
//		void setMute(WebView* caller, const JSArray& args);
//		void setInputString(WebView* caller, const JSArray& args);
//		void runInputString(WebView* caller, const JSArray& args);
//		void openGameFile(WebView* caller, const JSArray& args);
//		void runDefaultGame(WebView* caller, const JSArray& args);
//		void listLocalGames(WebView* caller, const JSArray& args);
//		void selectLocalGameInGamestock(WebView* caller, const JSArray& args);
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
//
//}
