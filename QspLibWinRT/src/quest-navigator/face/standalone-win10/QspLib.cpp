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
#include "AudioManager.h"
#include "PlaybackListener.h"
#include <ppltasks.h>

using namespace QuestNavigator;
using namespace concurrency;
using namespace Windows::Foundation;


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
		// Создаём объект для воспроизведения звуковых файлов.
		AudioManager* audioManager = new AudioManager();
		// Создаём объект для прослушивания событий воспроизведения.
		PlaybackListener^ playbackListener = ref new PlaybackListener();

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
			saveFileManager,
			audioManager
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
			saveFileManager,
			audioManager,
			fileSystemManager
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
			storagePathReader,
			fileSystemManager
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
		audioManager->inject(
			playbackListener,
			stringConverter,
			fileSystemManager,
			pathConverter
		);

		// Сохраняем публичное свойство 
		// для последующей привязки колбеков в яваскрипте
		// через объект UwpJsExecutor.
		this->uwpJsExecutor = uwpJsExecutor;
		// Сохраняем указатель на конвертер строк.
		this->stringConverter = stringConverter;
		// Сохраняем указатель на объект приложения.
		this->app = app;
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
	
	// Мы не можем блокировать поток UI и передать управление потоку библиотеки,
	// поэтому все вызовы API выносим в асинхронные задачи, выполняющиеся в фоновом потоке.
	// Если мы попытаемся выполнить вызовы напрямую из потока UI,
	// случится дедлок - поток UI будет ожидать библиотеку, 
	// а библиотека не сможет выполниться, пока не завершён вызов UI.

	void QspLib::init()
	{
		auto initTask = create_task(initAsync());
		initTask.then([](void) {});
	}

	void QspLib::restartGame()
	{
		auto restartGameTask = create_task(restartGameAsync());
		restartGameTask.then([](void) {});
	}

	void QspLib::executeAction(int32 pos)
	{
		auto executeActionTask = create_task(executeActionAsync(pos));
		executeActionTask.then([](void) {});
	}

	void QspLib::selectObject(int32 pos)
	{
		auto selectObjectTask = create_task(selectObjectAsync(pos));
		selectObjectTask.then([](void) {});
	}

	void QspLib::loadGame()
	{
		auto loadGameTask = create_task(loadGameAsync());
		loadGameTask.then([](void) {});
	}

	void QspLib::saveGame()
	{
		auto saveGameTask = create_task(saveGameAsync());
		saveGameTask.then([](void) {});
	}

	void QspLib::saveSlotSelected(int32 index, int32 mode)
	{
		auto saveSlotSelectedTask = create_task(saveSlotSelectedAsync(index, mode));
		saveSlotSelectedTask.then([](void) {});
	}

	void QspLib::msgResult()
	{
		auto msgResultTask = create_task(msgResultAsync());
		msgResultTask.then([](void) {});
	}

	void QspLib::errorResult()
	{
		auto errorResultTask = create_task(errorResultAsync());
		errorResultTask.then([](void) {});
	}

	void QspLib::userMenuResult(int32 pos)
	{
		auto userMenuResultTask = create_task(userMenuResultAsync(pos));
		userMenuResultTask.then([](void) {});
	}

	void QspLib::inputResult(Platform::String ^ text)
	{
		auto inputResultTask = create_task(inputResultAsync(text));
		inputResultTask.then([](void) {});
	}

	void QspLib::setMute(Platform::Boolean flag)
	{
		auto setMuteTask = create_task(setMuteAsync(flag));
		setMuteTask.then([](void) {});
	}

	void QspLib::setInputString(Platform::String ^ text)
	{
		auto setInputStringTask = create_task(setInputStringAsync(text));
		setInputStringTask.then([](void) {});
	}

	void QspLib::runInputString()
	{
		auto runInputStringTask = create_task(runInputStringAsync());
		runInputStringTask.then([](void) {});
	}

	void QspLib::runDefaultGame()
	{
		auto runDefaultGameTask = create_task(runDefaultGameAsync());
		runDefaultGameTask.then([](void) {});
	}

	void QspLib::execLink(Platform::String^ text)
	{
		auto execLinkTask = create_task(execLinkAsync(text));
		execLinkTask.then([](void) {});
	}

	// API

	// По приведению типов int, bool, wchar_t
	// см. таблицу
	// https://docs.microsoft.com/en-us/cpp/cppcx/fundamental-types-c-cx
	// По строкам и массивам см.
	// https://docs.microsoft.com/en-us/cpp/cppcx/type-system-c-cx

	IAsyncAction^ QspLib::initAsync()
	{
		return create_async([this]
		{
			// Запускаем приложение.
			//uwpJsExecutor->jsCallDebug("app->init(); start");
			app->init();
			//uwpJsExecutor->jsCallDebug("app->init(); finish");
		});
	}

	IAsyncAction^ QspLib::restartGameAsync()
	{
		return create_async([this]
		{
			//uwpJsExecutor->jsCallDebug("QspLib::restartGame() start");
			jsListener->restartGame();
			//uwpJsExecutor->jsCallDebug("QspLib::restartGame() finish");
		});
	}

	IAsyncAction^ QspLib::executeActionAsync(int32 pos)
	{
		return create_async([this, pos]
		{
			jsListener->executeAction((int)pos);
		});
	}

	IAsyncAction^ QspLib::selectObjectAsync(int32 pos)
	{
		return create_async([this, pos]
		{
			jsListener->selectObject((int)pos);
		});
	}

	IAsyncAction^ QspLib::loadGameAsync()
	{
		return create_async([this]
		{
			jsListener->loadGame();
		});
	}

	IAsyncAction^ QspLib::saveGameAsync()
	{
		return create_async([this]
		{
			jsListener->saveGame();
		});
	}

	IAsyncAction^ QspLib::saveSlotSelectedAsync(int32 index, int32 mode)
	{
		return create_async([this, index, mode]
		{
			jsListener->saveSlotSelected((int)index, (int)mode);
		});
	}

	IAsyncAction^ QspLib::msgResultAsync()
	{
		return create_async([this]
		{
			jsListener->msgResult();
		});
	}

	IAsyncAction^ QspLib::errorResultAsync()
	{
		return create_async([this]
		{
			jsListener->errorResult();
		});
	}

	IAsyncAction^ QspLib::userMenuResultAsync(int32 pos)
	{
		return create_async([this, pos]
		{
			jsListener->userMenuResult((int)pos);
		});
	}

	IAsyncAction^ QspLib::inputResultAsync(Platform::String ^ text)
	{
		return create_async([this, text]
		{
			jsListener->inputResult(stringConverter->convertUwpToStd(text));
		});
	}

	IAsyncAction^ QspLib::setMuteAsync(Platform::Boolean flag)
	{
		return create_async([this, flag]
		{
			jsListener->setMute((bool)flag);
		});
	}

	IAsyncAction^ QspLib::setInputStringAsync(Platform::String ^ text)
	{
		return create_async([this, text]
		{
			jsListener->setInputString(stringConverter->convertUwpToStd(text));
		});
	}

	IAsyncAction^ QspLib::runInputStringAsync()
	{
		return create_async([this]
		{
			jsListener->runInputString();
		});
	}

	IAsyncAction^ QspLib::runDefaultGameAsync()
	{
		return create_async([this]
		{
			jsListener->runDefaultGame();
		});
	}

	IAsyncAction^ QspLib::execLinkAsync(Platform::String^ text)
	{
		return create_async([this, text]
		{
			jsListener->execLink(stringConverter->convertUwpToStd(text));
		});
	}
}