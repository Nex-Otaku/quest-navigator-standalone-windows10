#include "pch.h"
#include "Library.h"
#include "..\..\core\dialogs.h"
#include <process.h>
#include "..\..\core\thread_sync.h"
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "..\..\core\skin.h"
#include "..\..\core\sound.h"
#include "..\..\core\events.h"

namespace QuestNavigator
{
	Library::Library()
	{
	}

	Library::~Library()
	{
	}

	void Library::inject(
		EventManager* eventManager
	)
	{
		this->eventManager = eventManager;
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
		// Сохраняем указатель на listener
		// STUB это нам надо?
		//listener = (QnApplicationListener*) pvParam;
	
		// Все функции библиотеки QSP (QSPInit и т.д.) 
		// вызываются только внутри потока библиотеки.

		// Инициализируем библиотеку
		QSPInit();
	
		// Привязываем колбэки
		//QSPSetCallBack(QSP_CALL_REFRESHINT, (QSP_CALLBACK)&RefreshInt);
		//QSPSetCallBack(QSP_CALL_SETTIMER, (QSP_CALLBACK)&SetTimer);
		//QSPSetCallBack(QSP_CALL_SETINPUTSTRTEXT, (QSP_CALLBACK)&SetInputStrText);
		//QSPSetCallBack(QSP_CALL_ISPLAYINGFILE, (QSP_CALLBACK)&IsPlayingFile);
		//QSPSetCallBack(QSP_CALL_PLAYFILE, (QSP_CALLBACK)&PlayFile);
		//QSPSetCallBack(QSP_CALL_CLOSEFILE, (QSP_CALLBACK)&CloseFile);
		//QSPSetCallBack(QSP_CALL_SHOWMSGSTR, (QSP_CALLBACK)&ShowMessage);
		//QSPSetCallBack(QSP_CALL_SLEEP, (QSP_CALLBACK)&Wait);
		//QSPSetCallBack(QSP_CALL_GETMSCOUNT, (QSP_CALLBACK)&GetMSCount);
		//QSPSetCallBack(QSP_CALL_DELETEMENU, (QSP_CALLBACK)&DeleteMenu);
		//QSPSetCallBack(QSP_CALL_ADDMENUITEM, (QSP_CALLBACK)&AddMenuItem);
		//QSPSetCallBack(QSP_CALL_SHOWMENU, (QSP_CALLBACK)&ShowMenu);
		//QSPSetCallBack(QSP_CALL_INPUTBOX, (QSP_CALLBACK)&InputBox);

		// STUB
		// Разобраться, почему не определена константа QSP_CALL_PLAYERINFO.
		// Неактуальные исходники? Не та ветка?
		//QSPSetCallBack(QSP_CALL_PLAYERINFO, (QSP_CALLBACK)&PlayerInfo);

		//QSPSetCallBack(QSP_CALL_SHOWIMAGE, (QSP_CALLBACK)&ShowPicture);
		//QSPSetCallBack(QSP_CALL_SHOWWINDOW, (QSP_CALLBACK)&ShowWindow);
		//QSPSetCallBack(QSP_CALL_SYSTEM, (QSP_CALLBACK)&System);
		//QSPSetCallBack(QSP_CALL_OPENGAMESTATUS, (QSP_CALLBACK)&OpenGameStatus);
		//QSPSetCallBack(QSP_CALL_SAVEGAMESTATUS, (QSP_CALLBACK)&SaveGameStatus);
	
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
			runSyncEvent(evLibIsReady);
			// Ожидаем любое из событий синхронизации
			DWORD res = WaitForMultipleObjects((DWORD)evLastUi, g_eventList, FALSE, INFINITE);
			if ((res < WAIT_OBJECT_0) || (res > (WAIT_OBJECT_0 + evLast - 1))) {
				showError("Не удалось дождаться множественного события синхронизации библиотеки.");
				bShutdown = true;
			} else {
				eSyncEvent ev = (eSyncEvent)res;
				switch (ev)
				{
				case evRunGame:
					{
						// Запуск игры
						string path = "";
						int isStandalone = 0;
						lockData();
						path = g_sharedData[evRunGame].str;
						isStandalone = g_sharedData[evRunGame].num;
						unlockData();
						QSP_BOOL res = QSPLoadGameWorld(widen(path).c_str());
						CheckQspResult(res, "QSPLoadGameWorld");
						// Очищаем скин
						Skin::resetUpdate();
						Skin::resetSettings();
						// Передаём настройку из конфига в скин.
						Skin::setInt(espIsStandalone, isStandalone);
						// Очищаем буфер JS-команд, передаваемых из игры
						jsExecBuffer = "";
	
						// Устанавливаем период выполнения и запускаем таймер
						SetTimer(500);
	
						//Запускаем счетчик миллисекунд
						gameStartTime = clock();
	
						res = QSPRestartGame(QSP_TRUE);
						CheckQspResult(res, "QSPRestartGame");
					}
					break;
				case evStopGame:
					{
						// Остановка игры
	
						// Останавливаем таймер.
						stopTimer();
	
						//останавливаем музыку
						CloseFile(NULL);
	
						// Очищаем буфер JS-команд, передаваемых из игры
						jsExecBuffer = "";
	
						runSyncEvent(evGameStopped);
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
						string code = "";
						lockData();
						code = g_sharedData[evExecuteCode].str;
						unlockData();
						wstring wCode = widen(code);
						QSP_BOOL res = QSPExecString(wCode.c_str(), QSP_TRUE);
						CheckQspResult(res, "QSPExecString");
					}
					break;
				case evExecuteAction:
					{
						// Выполнение действия
						int pos = 0;
						lockData();
						pos = g_sharedData[evExecuteAction].num;
						unlockData();
						QSP_BOOL res = QSPSetSelActionIndex(pos, QSP_FALSE);
						CheckQspResult(res, "QSPSetSelActionIndex");
						res = QSPExecuteSelActionCode(QSP_TRUE);
						CheckQspResult(res, "QSPExecuteSelActionCode");
					}
					break;
				case evSelectObject:
					{
						// Выбор предмета
						int pos = 0;
						lockData();
						pos = g_sharedData[evSelectObject].num;
						unlockData();
						// Костыль - следим за номером выбранного предмета,
						// так как иначе невозможно будет обновить
						// окно предметов при вызове UNSEL в ONOBJSEL.
						// Нужно исправить это в библиотеке QSP.
						objectSelectionIndex = -2;
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
						// Включение / выключение звука
						bool flag = false;
						lockData();
						flag = g_sharedData[evMute].flag;
						unlockData();
						SoundManager::mute(flag);
					}
					break;
				case evLoadSlotSelected:
					{
						int index = 0;
						lockData();
						index = g_sharedData[evLoadSlotSelected].num;
						unlockData();
						jsExecBuffer = "";
	
						string path = getRightPath(Configuration::getString(ecpSaveDir) + PATH_DELIMITER + to_string(index) + ".sav");
						if (!fileExists(path)) {
							showError("Не найден файл сохранения");
							break;
						}
	
						// Выключаем музыку
						CloseFile(NULL);
	
						// Загружаем сохранение
						QSP_BOOL res = QSPOpenSavedGame(widen(path).c_str(), QSP_TRUE);
						CheckQspResult(res, "QSPOpenSavedGame");
	
						// Запускаем таймер
						startTimer();
					}
					break;
				case evSaveSlotSelected:
					{
						int index = 0;
						lockData();
						index = g_sharedData[evSaveSlotSelected].num;
						unlockData();
						jsExecBuffer = "";
	
						string saveDir = Configuration::getString(ecpSaveDir);
						if (!dirExists(saveDir) && !buildDirectoryPath(saveDir)) {
							showError("Не удалось создать папку для сохранения: " + saveDir);
							break;
						}
	
						string path = getRightPath(saveDir + PATH_DELIMITER + to_string(index) + ".sav");
	
						QSP_BOOL res = QSPSaveGame(widen(path).c_str(), QSP_FALSE);
						CheckQspResult(res, "QSPSaveGame");
	
						startTimer();
					}
					break;
				case evInputStringChanged:
					{
						// Изменился текст в строке ввода
						string text = "";
						lockData();
						text = g_sharedData[evInputStringChanged].str;
						unlockData();
						QSPSetInputStrText(widen(text).c_str());
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
}