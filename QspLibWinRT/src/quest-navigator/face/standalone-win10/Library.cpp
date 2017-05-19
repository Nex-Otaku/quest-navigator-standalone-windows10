#include "pch.h"
#include "Library.h"
#include "..\..\core\dialogs.h"
#include <process.h>
#include "..\..\core\thread_sync.h"
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "..\..\core\skin.h"
#include "..\..\core\sound.h"
#include "..\..\core\events.h"
#include "..\..\core\encoding.h"
#include "LibraryListener.h"
#include "Timer.h"

namespace QuestNavigator
{
	Library::Library()
	{
	}

	Library::~Library()
	{
	}

	void Library::inject(
		EventManager* eventManager,
		Timer* timer
	)
	{
		this->eventManager = eventManager;
		this->timer = timer;
	}

	// ********************************************************************
	// Переменные библиотеки
	// ********************************************************************
	
	//QnApplicationListener* QnApplicationListener::listener = NULL;

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

		libThread = (HANDLE)_beginthreadex(NULL, 0, &Library::libThreadFunc, this, 0, NULL);
		if (libThread == NULL) {
			showError("Не получилось создать поток интерпретатора.");

			// STUB
			// Сделать выход из приложения?
			//exit(eecFailToBeginLibThread);
			return;
		}
	}

	// Остановка потока библиотеки. Вызывается только раз при завершении программы.
	void Library::StopLibThread()
	{
		if (libThread == NULL)
			return;

		// Сообщаем потоку библиотеки, что нужно завершить работу
		this->eventManager->shutdown();
		// Ждём завершения библиотечного потока
		waitForSingle(libThread);
		// Закрываем хэндл библиотечного потока
		freeHandle(libThread);
		libThread = NULL;

		this->eventManager->freeEvents();
		this->eventManager->freeSharedData();
	}

	// Основная функция потока библиотеки. Вызывается только раз за весь жизненный цикл программы.
	unsigned int Library::libThreadFunc(void* pvParam)
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

		// STUB
		// Разобраться, почему не определена константа QSP_CALL_PLAYERINFO.
		// Неактуальные исходники? Не та ветка?
		//QSPSetCallBack(QSP_CALL_PLAYERINFO, (QSP_CALLBACK)&PlayerInfo);

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
			library->eventManager->libIsReady();
			// Ожидаем любое из событий синхронизации
			DWORD res = library->eventManager->waitForAnyEvent();
			if (!library->eventManager->isValidEvent(res)) {
				showError("Не удалось дождаться множественного события синхронизации библиотеки.");
				bShutdown = true;
			} else {
				eSyncEvent ev = (eSyncEvent)res;
				switch (ev)
				{
				case evRunGame:
					{
						// Запуск игры
						SharedDataDto dto = library->eventManager->getSharedData(ev);
						string path = dto.str;
						int isStandalone = dto.num;
						QSP_BOOL res = QSPLoadGameWorld(widen(path).c_str());
						CheckQspResult(res, "QSPLoadGameWorld");
						// Очищаем скин
						Skin::resetUpdate();
						Skin::resetSettings();
						// Передаём настройку из конфига в скин.
						Skin::setInt(espIsStandalone, isStandalone);
						// Очищаем буфер JS-команд, передаваемых из игры
						LibraryListener::resetJsExecBuffer();
	
						// Устанавливаем период выполнения и запускаем таймер
						LibraryListener::SetTimer(500);
	
						//Запускаем счетчик миллисекунд
						LibraryListener::resetMsCount();
	
						res = QSPRestartGame(QSP_TRUE);
						CheckQspResult(res, "QSPRestartGame");
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
						CheckQspResult(res, "QSPExecString");
					}
					break;
				case evExecuteAction:
					{
						// Выполнение действия
						SharedDataDto dto = library->eventManager->getSharedData(evExecuteAction);
						int pos = dto.num;
						QSP_BOOL res = QSPSetSelActionIndex(pos, QSP_FALSE);
						CheckQspResult(res, "QSPSetSelActionIndex");
						res = QSPExecuteSelActionCode(QSP_TRUE);
						CheckQspResult(res, "QSPExecuteSelActionCode");
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
						CheckQspResult(res, "QSPSetSelObjectIndex");
					}
					break;
				case evTimer:
					{
						// Таймер
						QSP_BOOL res = QSPExecCounter(QSP_TRUE);
						CheckQspResult(res, "QSPExecCounter");
					}
					break;
				case evMute:
					{
						//// Включение / выключение звука
						//bool flag = false;
						//lockData();
						//flag = g_sharedData[evMute].flag;
						//unlockData();
						//SoundManager::mute(flag);
					}
					break;
				case evLoadSlotSelected:
					{
						//int index = 0;
						//lockData();
						//index = g_sharedData[evLoadSlotSelected].num;
						//unlockData();
						//LibraryListener::resetJsExecBuffer();
	
						//string path = getRightPath(Configuration::getString(ecpSaveDir) + PATH_DELIMITER + to_string(index) + ".sav");
						//if (!fileExists(path)) {
						//	showError("Не найден файл сохранения");
						//	break;
						//}
	
						//// Выключаем музыку
						//CloseFile(NULL);
	
						//// Загружаем сохранение
						//QSP_BOOL res = QSPOpenSavedGame(widen(path).c_str(), QSP_TRUE);
						//CheckQspResult(res, "QSPOpenSavedGame");
	
						//// Запускаем таймер
						//startTimer();
					}
					break;
				case evSaveSlotSelected:
					{
						//int index = 0;
						//lockData();
						//index = g_sharedData[evSaveSlotSelected].num;
						//unlockData();
						//LibraryListener::resetJsExecBuffer();
	
						//string saveDir = Configuration::getString(ecpSaveDir);
						//if (!dirExists(saveDir) && !buildDirectoryPath(saveDir)) {
						//	showError("Не удалось создать папку для сохранения: " + saveDir);
						//	break;
						//}
	
						//string path = getRightPath(saveDir + PATH_DELIMITER + to_string(index) + ".sav");
	
						//QSP_BOOL res = QSPSaveGame(widen(path).c_str(), QSP_FALSE);
						//CheckQspResult(res, "QSPSaveGame");
	
						//startTimer();
					}
					break;
				case evInputStringChanged:
					{
						//// Изменился текст в строке ввода
						//string text = "";
						//lockData();
						//text = g_sharedData[evInputStringChanged].str;
						//unlockData();
						//QSPSetInputStrText(widen(text).c_str());
					}
					break;
				case evInputStringEntered:
					{
						QSP_BOOL res = QSPExecUserInput(QSP_TRUE);
						CheckQspResult(res, "QSPExecUserInput");
					}
					break;
				default:
					{
						showError("Необработанное событие синхронизации!");
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
		_endthreadex(0);
		return 0;
	}

	// Проверяем статус выполнения операции и сообщаем об ошибке, если требуется.
	void Library::CheckQspResult(QSP_BOOL successfull, string failMsg)
	{
		//Контекст библиотеки
		//if (successfull == QSP_FALSE)
		//{
		//	//Контекст библиотеки
		//	int line = -1;
		//	int actIndex = -1;
		//	string desc = "";
		//	string loc = "";
		//	int errorNum = -1;
		//	QSP_CHAR* pErrorLoc = NULL;
		//	QSPGetLastErrorData(&errorNum, &pErrorLoc, &actIndex, &line);
		//	loc = Skin::applyHtmlFixes(fromQsp(pErrorLoc));
		//	desc = Skin::applyHtmlFixes(fromQsp(QSPGetErrorDesc(errorNum)));
	
		//	// Обновляем скин
		//	Skin::updateBaseVars();
		//	Skin::updateMsgDialog();
		//	// Если что-то изменилось, то передаем в яваскрипт
		//	if (Skin::isSomethingChanged())
		//	{
		//		RefreshInt(QSP_TRUE);
		//	}
	
		//	JSObject jsErrorContainer;
		//	jsErrorContainer.SetProperty(WSLit("desc"), ToWebString(desc));
		//	jsErrorContainer.SetProperty(WSLit("loc"), ToWebString(loc));
		//	jsErrorContainer.SetProperty(WSLit("actIndex"), JSValue(actIndex));
		//	jsErrorContainer.SetProperty(WSLit("line"), JSValue(line));
	
		//	// Передаём данные в поток UI
		//	qspError(jsErrorContainer);
	
		//	// Ждём закрытия диалога
		//	waitForSingleLib(evErrorClosed);
		//}
	}
}