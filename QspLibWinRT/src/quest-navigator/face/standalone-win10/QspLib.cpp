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
#include "..\..\platform\windows10\StringConverter.h"
#include "..\..\platform\windows10\ThreadManager.h"
#include "..\..\platform\windows10\ThreadApi.h"
#include "GameFileManager.h"
#include "JsonSerializer.h"
#include "PathConverter.h"
#include "..\..\platform\windows10\FileSystemApiWin32.h"
#include "FileSystemManager.h"
#include "SaveFileManager.h"
#include "..\..\platform\windows10\ApplicationPathReader.h"
#include "..\..\platform\windows10\StoragePathReader.h"

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
		// Создаём билдер конфигурации.
		ConfigurationBuilder* configurationBuilder = new ConfigurationBuilder();
		// Создаём конвертер для платформенных строк.
		StringConverter* stringConverter = new StringConverter();
		// Создаём объект для управления потоками.
		ThreadManager* threadManager = new ThreadManager();
		// Создаём объект для обёртки платформенной реализации поточных функций.
		ThreadApi* threadApi = new ThreadApi();
		// Создаём объект для управления файлом игры.
		GameFileManager* gameFileManager = new GameFileManager();
		// Создаём объект для сериализации DTO в строки JSON.
		JsonSerializer* jsonSerializer = new JsonSerializer();
		// Создаём объект для конвертации путей.
		PathConverter* pathConverter = new PathConverter();
		// Создаём объект для чтения пути приложения.
		ApplicationPathReader* applicationPathReader = new ApplicationPathReader();
		// Создаём объект для платформенной обёртки функций файловой системы для Windows32 API.
		FileSystemApiWin32* fileSystemApiWin32 = new FileSystemApiWin32();
		// Создаём объект для управления файловой системой.
		FileSystemManager* fileSystemManager = new FileSystemManager();
		// Создаём объект для управления сейвами.
		SaveFileManager* saveFileManager = new SaveFileManager();
		// Создаём объект для чтения пути к локальному хранилищу - в хранилище мы записываем сейвы.
		StoragePathReader* storagePathReader = new StoragePathReader();

		// Делаем инъекцию зависимостей.
		jsListener->inject(
			eventManager,
			app,
			timer,
			jsExecutor,
			saveFileManager
		);
		app->inject(
			eventManager,
			library,
			configurationBuilder
		);
		library->inject(
			eventManager,
			timer,
			jsExecutor,
			threadManager,
			saveFileManager
		);
		eventManager->inject(
			timer, 
			uwpJsExecutor, 
			stringConverter,
			threadManager
		);
		libraryListener->inject(
			jsExecutor,
			timer,
			eventManager,
			library,
			pathConverter,
			saveFileManager
		);
		jsExecutor->inject(
			uwpJsExecutor, 
			stringConverter,
			jsonSerializer
		);
		errorDebugReporter->inject(
			uwpJsExecutor, 
			stringConverter
		);
		threadManager->inject(threadApi);
		configurationBuilder->inject(
			gameFileManager,
			storagePathReader
		);
		gameFileManager->inject(applicationPathReader);
		jsonSerializer->inject(stringConverter);
		pathConverter->inject(applicationPathReader);
		saveFileManager->inject(
			library,
			fileSystemManager
		);
		fileSystemManager->inject(
			fileSystemApiWin32
		);
		applicationPathReader->inject(stringConverter);
		storagePathReader->inject(stringConverter);

		// Сохраняем публичное свойство 
		// для последующей привязки колбеков в яваскрпите
		// через объект UwpJsExecutor.
		this->uwpJsExecutor = uwpJsExecutor;
		// Сохраняем указатель на конвертер строк.
		this->stringConverter = stringConverter;

		// Запускаем приложение.
		this->uwpJsExecutor->jsCallDebug("app->init(); start");
		app->init();
		this->uwpJsExecutor->jsCallDebug("app->init(); finish");
	}

	UwpJsExecutor^ QspLib::getUwpJsExecutor()
	{
		return uwpJsExecutor;
	}

	void QspLib::callDebugMessage()
	{
		uwpJsExecutor->jsCallDebug("simple debug call");
	}

	// Колбэки из яваскрипта к функциям API плеера.

	// По приведению типов int, bool, wchar_t
	// см. таблицу
	// https://docs.microsoft.com/en-us/cpp/cppcx/fundamental-types-c-cx
	// По строкам и массивам см.
	// https://docs.microsoft.com/en-us/cpp/cppcx/type-system-c-cx

	void QspLib::restartGame()
	{
		//this->uwpJsExecutor->jsCallDebug("QspLib::restartGame() start");
		jsListener->restartGame();
		//this->uwpJsExecutor->jsCallDebug("QspLib::restartGame() finish");
	}

	void QspLib::executeAction(int32 pos)
	{
		jsListener->executeAction((int)pos);
	}

	void QspLib::selectObject(int32 pos)
	{
		jsListener->selectObject((int)pos);
	}

	void QspLib::loadGame()
	{
		jsListener->loadGame();
	}

	void QspLib::saveGame()
	{
		jsListener->saveGame();
	}

	void QspLib::saveSlotSelected(int32 index, int32 mode)
	{
		jsListener->saveSlotSelected((int)index, (int)mode);
	}

	void QspLib::msgResult()
	{
		jsListener->msgResult();
	}

	void QspLib::errorResult()
	{
		jsListener->errorResult();
	}

	void QspLib::userMenuResult(int32 pos)
	{
		jsListener->userMenuResult((int)pos);
	}

	void QspLib::inputResult(Platform::String ^ text)
	{
		jsListener->inputResult(stringConverter->convertUwpToStd(text));
	}

	void QspLib::setMute(Platform::Boolean flag)
	{
		jsListener->setMute((bool)flag);
	}

	void QspLib::setInputString(Platform::String ^ text)
	{
		jsListener->setInputString(stringConverter->convertUwpToStd(text));
	}

	void QspLib::runInputString()
	{
		jsListener->runInputString();
	}

	void QspLib::runDefaultGame()
	{
		jsListener->runDefaultGame();
	}

	void QspLib::execLink(Platform::String^ text)
	{
		jsListener->execLink(stringConverter->convertUwpToStd(text));
	}
}