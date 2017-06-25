#include "pch.h"
#include "Library.h"
#include "..\..\core\dialogs.h"
#include <process.h>
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "..\..\core\skin.h"
#include "..\..\core\sound.h"
#include "..\..\core\events.h"
#include "..\..\core\encoding.h"
#include "LibraryListener.h"
#include "Timer.h"
#include "..\..\core\files.h"
#include "..\..\core\dto\ErrorDto.h"
#include "Constants.h"
#include "..\..\platform\windows10\ThreadEmulation.h"

namespace QuestNavigator
{
	Library::Library() 
		: libThread(NULL)
	{
	}

	Library::~Library()
	{
	}

	void Library::inject(
		EventManager* eventManager,
		Timer* timer,
		JsExecutor* jsExecutor,
		ThreadManager* threadManager
	)
	{
		this->eventManager = eventManager;
		this->timer = timer;
		this->jsExecutor = jsExecutor;
		this->threadManager = threadManager;
	}

	// Запуск потока библиотеки. Вызывается только раз при старте программы.
	void Library::StartLibThread()
	{
		//Контекст UI
		if (libThread != NULL)
		{
			showError("StartLibThread: failed, libThread is not null");

			// STUB
			// Сделать выход из приложения?
			//exit(eecLibThreadAlreadyStarted);
			return;
		}

		this->eventManager->initEvents();
		this->eventManager->initSharedData();

		//libThread = (HANDLE)_beginthread(NULL, 0, &Library::libThreadFunc, this, 0, NULL);
		LPTHREAD_START_ROUTINE pLibThreadFunc = &Library::libThreadFunc;
		//libThread = (HANDLE)UwpCustomBeginThread(NULL, 0, pLibThreadFunc, this, 0, NULL);
		//libThread = (HANDLE)ThreadEmulation::CreateThread(NULL, 0, pLibThreadFunc, this, 0, NULL);
		libThread = threadManager->CreateThread(pLibThreadFunc, this);
		if (libThread == NULL) {
			showError("Не получилось создать поток интерпретатора.");

			// STUB
			// Сделать выход из приложения?
			//exit(eecFailToBeginLibThread);
			return;
		}
		showError("StartLibThread: success, libThread created");
	}

	// Остановка потока библиотеки. Вызывается только раз при завершении программы.
	void Library::StopLibThread()
	{
		if (libThread == NULL)
			return;

		// Сообщаем потоку библиотеки, что нужно завершить работу
		this->eventManager->shutdown();
		// Ждём завершения библиотечного потока
		threadManager->waitForSingle(libThread);
		// Закрываем хэндл библиотечного потока
		threadManager->freeHandle(libThread);
		libThread = NULL;

		this->eventManager->freeEvents();
		this->eventManager->freeSharedData();
	}

	// Основная функция потока библиотеки. Вызывается только раз за весь жизненный цикл программы.
	//unsigned int Library::libThreadFunc(void* pvParam)
	DWORD Library::libThreadFunc(LPVOID pvParam)
	{
		// Сохраняем указатель на объект Library.
		Library* library = (Library*)pvParam;
	
		// Все функции библиотеки QSP (QSPInit и т.д.) 
		// вызываются только внутри потока библиотеки.

		// Инициализируем библиотеку
		QSPInit();
	
		// Привязываем колбэки
		QSPSetCallBack(QSP_CALL_REFRESHINT, (QSP_CALLBACK)&LibraryListener::RefreshInt);
		QSPSetCallBack(QSP_CALL_SETTIMER, (QSP_CALLBACK)&LibraryListener::SetTimer);
		QSPSetCallBack(QSP_CALL_SETINPUTSTRTEXT, (QSP_CALLBACK)&LibraryListener::SetInputStrText);
		QSPSetCallBack(QSP_CALL_ISPLAYINGFILE, (QSP_CALLBACK)&LibraryListener::IsPlayingFile);
		QSPSetCallBack(QSP_CALL_PLAYFILE, (QSP_CALLBACK)&LibraryListener::PlayFile);
		QSPSetCallBack(QSP_CALL_CLOSEFILE, (QSP_CALLBACK)&LibraryListener::CloseFile);
		QSPSetCallBack(QSP_CALL_SHOWMSGSTR, (QSP_CALLBACK)&LibraryListener::ShowMessage);
		QSPSetCallBack(QSP_CALL_SLEEP, (QSP_CALLBACK)&LibraryListener::Wait);
		QSPSetCallBack(QSP_CALL_GETMSCOUNT, (QSP_CALLBACK)&LibraryListener::GetMSCount);
		QSPSetCallBack(QSP_CALL_DELETEMENU, (QSP_CALLBACK)&LibraryListener::DeleteMenu);
		QSPSetCallBack(QSP_CALL_ADDMENUITEM, (QSP_CALLBACK)&LibraryListener::AddMenuItem);
		QSPSetCallBack(QSP_CALL_SHOWMENU, (QSP_CALLBACK)&LibraryListener::ShowMenu);
		QSPSetCallBack(QSP_CALL_INPUTBOX, (QSP_CALLBACK)&LibraryListener::InputBox);
		QSPSetCallBack(QSP_CALL_PLAYERINFO, (QSP_CALLBACK)&LibraryListener::PlayerInfo);
		QSPSetCallBack(QSP_CALL_SHOWIMAGE, (QSP_CALLBACK)&LibraryListener::ShowPicture);
		QSPSetCallBack(QSP_CALL_SHOWWINDOW, (QSP_CALLBACK)&LibraryListener::ShowWindow);
		QSPSetCallBack(QSP_CALL_SYSTEM, (QSP_CALLBACK)&LibraryListener::System);
		QSPSetCallBack(QSP_CALL_OPENGAMESTATUS, (QSP_CALLBACK)&LibraryListener::OpenGameStatus);
		QSPSetCallBack(QSP_CALL_SAVEGAMESTATUS, (QSP_CALLBACK)&LibraryListener::SaveGameStatus);
	
		// Заполняем значения по умолчанию для скина
		Skin::initDefaults();
	
		// Флаг для завершения потока
		bool bShutdown = false;
	
		// Запускаем движок Audiere для проигрывания звуковых файлов
		if (!SoundManager::init()) {
			bShutdown = true;
		}
	
		// Обработка событий происходит в цикле
		while (!bShutdown) {
			// Сообщаем потоку UI, что библиотека готова к выполнению команд
			//showError("library->eventManager->libIsReady();");
			bool libIsReadyIsPosted = library->eventManager->setLibIsReady();
			if (!libIsReadyIsPosted) {
				showError("Library::libThreadFunc Не удалось сообщить о готовности библиотеки.");
				break;
			}
			//showError("Library thread called libIsReady");
			// Ожидаем любое из событий синхронизации
			DWORD res = library->eventManager->waitForAnyEvent();
			if (!library->eventManager->isValidEvent(res)) {
				showError("Library::libThreadFunc Не удалось дождаться множественного события синхронизации библиотеки.");
				bShutdown = true;
			} else {
				eSyncEvent ev = (eSyncEvent)res;
				switch (ev)
				{
				case evRunGame:
					{
						//showError("Library::libThreadFunc ============ evRunGame start ============");
						// Запуск игры
						SharedDataDto dto = library->eventManager->getSharedData(ev);
						//showError("Library::libThreadFunc ============ evRunGame 1 ============");
						string path = dto.str;
						//showError("Library::libThreadFunc ============ evRunGame 2 ============");
						int isStandalone = dto.num;

						//showError("Library::libThreadFunc ============ evRunGame 3 ============");
						// Очищаем скин.
						// Если будем выводить ошибку в CheckQspResult,
						// нам понадобится уже готовый скин.
						// Поэтому готовим его заранее.
						Skin::resetUpdate();
						//showError("Library::libThreadFunc ============ evRunGame 4 ============");
						Skin::resetSettings();
						//showError("Library::libThreadFunc ============ evRunGame 5 ============");
						// Передаём настройку из конфига в скин.
						Skin::setInt(espIsStandalone, isStandalone);
						//showError("Library::libThreadFunc ============ evRunGame 6 ============");

						//showError("Library::libThreadFunc ============ evRunGame load from " + path);
						QSP_BOOL res = QSPLoadGameWorld(widen(path).c_str());
						//showError("Library::libThreadFunc ============ evRunGame 7 ============");
						library->CheckQspResult(res, "QSPLoadGameWorld");
						//showError("Library::libThreadFunc ============ evRunGame 8 ============");
						// Очищаем буфер JS-команд, передаваемых из игры
						LibraryListener::resetJsExecBuffer();
						//showError("Library::libThreadFunc ============ evRunGame 9 ============");

						// Устанавливаем период выполнения и запускаем таймер
						LibraryListener::SetTimer(500);
						//showError("Library::libThreadFunc ============ evRunGame 10 ============");

						//Запускаем счетчик миллисекунд
						LibraryListener::resetMsCount();
						//showError("Library::libThreadFunc ============ evRunGame 11 ============");

						res = QSPRestartGame(QSP_TRUE);
						//showError("Library::libThreadFunc ============ evRunGame 12 ============");
						library->CheckQspResult(res, "QSPRestartGame");
						//showError("Library::libThreadFunc ============ evRunGame finish ============");
				}
					break;
				case evStopGame:
					{
						// Остановка игры
	
						// Останавливаем таймер.
						library->timer->stopTimer();
	
						//останавливаем музыку
						LibraryListener::CloseFile(NULL);
	
						// Очищаем буфер JS-команд, передаваемых из игры
						LibraryListener::resetJsExecBuffer();
	
						library->eventManager->gameStopped();
					}
					break;
				case evShutdown:
					{
						// Завершение работы
						bShutdown = true;
					}
					break;
				case evExecuteCode:
					{
						// Выполнение строки кода
						SharedDataDto dto = library->eventManager->getSharedData(evExecuteCode);
						string code = dto.str;
						wstring wCode = widen(code);
						QSP_BOOL res = QSPExecString(wCode.c_str(), QSP_TRUE);
						library->CheckQspResult(res, "QSPExecString");
					}
					break;
				case evExecuteAction:
					{
						// Выполнение действия
						SharedDataDto dto = library->eventManager->getSharedData(evExecuteAction);
						int pos = dto.num;
						QSP_BOOL res = QSPSetSelActionIndex(pos, QSP_FALSE);
						library->CheckQspResult(res, "QSPSetSelActionIndex");
						res = QSPExecuteSelActionCode(QSP_TRUE);
						library->CheckQspResult(res, "QSPExecuteSelActionCode");
					}
					break;
				case evSelectObject:
					{
						// Выбор предмета
						SharedDataDto dto = library->eventManager->getSharedData(evSelectObject);
						int pos = dto.num;
						// Костыль - следим за номером выбранного предмета,
						// так как иначе невозможно будет обновить
						// окно предметов при вызове UNSEL в ONOBJSEL.
						// Нужно исправить это в библиотеке QSP.
						LibraryListener::setObjectSelectionIndex(-2);
						QSP_BOOL res = QSPSetSelObjectIndex(pos, QSP_TRUE);
						library->CheckQspResult(res, "QSPSetSelObjectIndex");
					}
					break;
				case evTimer:
					{
						// Таймер
						QSP_BOOL res = QSPExecCounter(QSP_TRUE);
						library->CheckQspResult(res, "QSPExecCounter");
					}
					break;
				case evMute:
					{
						// Включение / выключение звука
						SharedDataDto dto = library->eventManager->getSharedData(evMute);
						bool flag = dto.flag;
						SoundManager::mute(flag);
					}
					break;
				case evLoadSlotSelected:
					{
						SharedDataDto dto = library->eventManager->getSharedData(evLoadSlotSelected);
						int index = dto.num;
						LibraryListener::resetJsExecBuffer();
	
						//string path = getRightPath(Configuration::getString(ecpSaveDir) + PATH_DELIMITER + to_string(index) + ".sav");
						string path = to_string(index) + ".sav";
						//if (!fileExists(path)) {
						//	showError("Library::libThreadFunc Не найден файл сохранения");
						//	break;
						//}
	
						// Выключаем музыку
						LibraryListener::CloseFile(NULL);
	
						// Загружаем сохранение
						//QSP_BOOL res = QSPOpenSavedGame(widen(path).c_str(), QSP_TRUE);
						//library->CheckQspResult(res, "QSPOpenSavedGame");

						library->saveFileManager->readSaveFile(path, true);
	
						// Запускаем таймер
						library->timer->startTimer();
					}
					break;
				case evSaveSlotSelected:
					{
						SharedDataDto dto = library->eventManager->getSharedData(evSaveSlotSelected);
						int index = dto.num;
						LibraryListener::resetJsExecBuffer();

						// STUB

						//string saveDir = Configuration::getString(ecpSaveDir);
						//string path = getRightPath(saveDir + PATH_DELIMITER + to_string(index) + ".sav");
						string path = to_string(index) + ".sav";

						library->saveFileManager->writeSaveFile(path);
	
						//string saveDir = Configuration::getString(ecpSaveDir);
						//if (!dirExists(saveDir) && !library->fileSystemManager->buildDirectoryPath(saveDir)) {
						//	showError("Library::libThreadFunc Не удалось создать папку для сохранения: " + saveDir);
						//	break;
						//}
	
						//string path = getRightPath(saveDir + PATH_DELIMITER + to_string(index) + ".sav");
	
						//QSP_BOOL res = QSPSaveGame(widen(path).c_str(), QSP_FALSE);
						//library->CheckQspResult(res, "QSPSaveGame");
	
						library->timer->startTimer();
					}
					break;
				case evInputStringChanged:
					{
						// Изменился текст в строке ввода
						SharedDataDto dto = library->eventManager->getSharedData(evInputStringChanged);
						string text = dto.str;
						QSPSetInputStrText(widen(text).c_str());
					}
					break;
				case evInputStringEntered:
					{
						QSP_BOOL res = QSPExecUserInput(QSP_TRUE);
						library->CheckQspResult(res, "QSPExecUserInput");
					}
					break;
				default:
					{
						showError("Library::libThreadFunc Необработанное событие синхронизации! Код события: " + std::to_string((int)ev));
						bShutdown = true;
					}
					break;
				}
			}
		}
	
		// Останавливаем звуковой движок
		SoundManager::close(true, "");
		SoundManager::deinit();
	
		// Завершаем работу библиотеки
		QSPDeInit();
		// Завершаем работу потока
		// STUB Так как мы не используем _beginthreadex, то здесь что-то надо придумать.
		//_endthreadex(0);
		return 0;
	}

	// Проверяем статус выполнения операции и сообщаем об ошибке, если требуется.
	void Library::CheckQspResult(QSP_BOOL successfull, string failMsg)
	{
		//Контекст библиотеки
		if (successfull == QSP_FALSE)
		{
			//Контекст библиотеки
			int line = -1;
			int actIndex = -1;
			string desc = "";
			string loc = "";
			int errorNum = -1;
			QSP_CHAR* pErrorLoc = NULL;
			QSPGetLastErrorData(&errorNum, &pErrorLoc, &actIndex, &line);
			showError("QSP core library error: " + std::to_string((int)errorNum));
			loc = Skin::applyHtmlFixes(fromQsp(pErrorLoc));
			desc = Skin::applyHtmlFixes(fromQsp(QSPGetErrorDesc(errorNum)));
	
			// Обновляем скин
			Skin::updateBaseVars();
			Skin::updateMsgDialog();
			// Если что-то изменилось, то передаем в яваскрипт
			if (Skin::isSomethingChanged())
			{
				LibraryListener::RefreshInt(QSP_TRUE);
			}
	
			ErrorDto errorDto;
			errorDto.desc = desc;
			errorDto.loc = loc;
			errorDto.actIndex = actIndex;
			errorDto.line = line;
	
			// Передаём данные в поток UI
			this->jsExecutor->qspError(errorDto);
	
			// Ждём закрытия диалога
			this->eventManager->waitForErrorClosed();
		}
	}
}