#include "pch.h"
#include "QspLib.h"
#include "EventManager.h"
#include "Timer.h"
#include "App.h"
#include "JsExecutor.h"
#include "Library.h"

using namespace QuestNavigator;

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
		// Создаём объект для управления потоком библиотеки.
		Library* library = new Library();

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
	}

	// Колбэки из яваскрипта к функциям API плеера.

	// По приведению типов int, bool, wchar_t
	// см. таблицу
	// https://docs.microsoft.com/en-us/cpp/cppcx/fundamental-types-c-cx
	// По строкам и массивам см.
	// https://docs.microsoft.com/en-us/cpp/cppcx/type-system-c-cx

	void QspLib::restartGame()
	{
		this->jsListener->restartGame();
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