#include "pch.h"
#include "QspLib.h"
#include "EventManager.h"
#include "Timer.h"
#include "App.h"
#include "JsExecutor.h"
#include "Library.h"
#include "LibraryListener.h"
#include "..\..\platform\windows10\UwpJsExecutor.h"
#include "..\..\platform\windows10\ErrorDebugReporter.h"

using namespace QuestNavigator;
using namespace QspLibWinRT;

namespace QspLibWinRT
{

	QspLib::QspLib()
	{
		// Этот файл является корневым для приложения.
		// Так называемая "точка сборки".
		// Именно здесь мы указываем, какие реализации интерфейсов следует применять,
		// и соответственно создаём все конкретные объекты, привязываем зависимости.

		// Создаём объект, который будет "слушать" вызовы яваскриптового API.
		this->jsListener = new JsListener();
		// Создаём обработчик событий.
		// События используются для синхронизации и передачи данных между потоками.
		EventManager* eventManager = new EventManager();
		// Создаём объект для управления таймером.
		Timer* timer = new Timer();
		// Создаём объект приложения.
		App* app = new App();
		// Создаём объект для выполнения яваскрипта.
		JsExecutor* jsExecutor = new JsExecutor();
		// Создаём вспомогательный объект для выполнения яваскрипта, 
		// который работает непосредственно на уровне платформы.
		UwpJsExecutor^ uwpJsExecutor = ref new UwpJsExecutor();
		// Создаём объект для управления потоком библиотеки.
		Library* library = new Library();
		// Создаём синглтон-объект для обработки колбеков библиотеки.
		LibraryListener* libraryListener = LibraryListener::instance();
		// Создаём объект для вывода ошибок - в целях отладки.
		ErrorDebugReporter* errorDebugReporter = ErrorDebugReporter::instance();

		// Делаем инъекцию зависимостей.
		this->jsListener->inject(
			eventManager,
			app,
			timer,
			jsExecutor
		);
		app->inject(
			eventManager,
			library
		);
		library->inject(
			eventManager,
			timer,
			jsExecutor
		);
		eventManager->inject(timer, uwpJsExecutor);
		libraryListener->inject(
			jsExecutor,
			timer,
			eventManager,
			library
		);
		jsExecutor->inject(uwpJsExecutor);
		errorDebugReporter->inject(uwpJsExecutor);

		// Сохраняем публичное свойство 
		// для последующей привязки колбеков в яваскрпите
		// через объект UwpJsExecutor.
		this->uwpJsExecutor = uwpJsExecutor;

		// Запускаем приложение.
		app->init();
	}

	UwpJsExecutor^ QspLib::getUwpJsExecutor()
	{
		return this->uwpJsExecutor;
	}

	void QspLib::callDebugMessage()
	{
		this->uwpJsExecutor->jsCallDebug("simple debug call");
	}

	// Колбэки из яваскрипта к функциям API плеера.

	// По приведению типов int, bool, wchar_t
	// см. таблицу
	// https://docs.microsoft.com/en-us/cpp/cppcx/fundamental-types-c-cx
	// По строкам и массивам см.
	// https://docs.microsoft.com/en-us/cpp/cppcx/type-system-c-cx

	void QspLib::restartGame()
	{
		this->uwpJsExecutor->jsCallDebug("QspLib::restartGame() start");
		this->jsListener->restartGame();
		this->uwpJsExecutor->jsCallDebug("QspLib::restartGame() finish");
	}

	void QspLib::executeAction(int32 pos)
	{
		this->jsListener->executeAction((int)pos);
	}

	void QspLib::selectObject(int32 pos)
	{
		this->jsListener->selectObject((int)pos);
	}

	void QspLib::loadGame()
	{
		this->jsListener->loadGame();
	}

	void QspLib::saveGame()
	{
		this->jsListener->saveGame();
	}

	void QspLib::saveSlotSelected(int32 index, int32 mode)
	{
		this->jsListener->saveSlotSelected((int)index, (int)mode);
	}

	void QspLib::msgResult()
	{
		this->jsListener->msgResult();
	}

	void QspLib::errorResult()
	{
		this->jsListener->errorResult();
	}

	void QspLib::userMenuResult(int32 pos)
	{
		this->jsListener->userMenuResult((int)pos);
	}

	void QspLib::inputResult(Platform::String ^ text)
	{
		throw ref new Platform::NotImplementedException();
		//this->jsListener->inputResult((string)text);
	}

	void QspLib::setMute(Platform::Boolean flag)
	{
		this->jsListener->setMute((bool)flag);
	}

	void QspLib::setInputString(Platform::String ^ text)
	{
		throw ref new Platform::NotImplementedException();
		//this->jsListener->setInputString((string)text);
	}

	void QspLib::runInputString()
	{
		this->jsListener->runInputString();
	}

	void QspLib::runDefaultGame()
	{
		this->jsListener->runDefaultGame();
	}
}