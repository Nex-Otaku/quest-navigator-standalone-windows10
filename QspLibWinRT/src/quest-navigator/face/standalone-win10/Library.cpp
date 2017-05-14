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

	// ������ ������ ����������. ���������� ������ ��� ��� ������ ���������.
	void Library::StartLibThread()
	{
		//�������� UI
		if (libThread != NULL)
		{
			showError("StartLibThread: failed, libThread is not null");

			// STUB
			// ������� ����� �� ����������?
			//exit(eecLibThreadAlreadyStarted);
			return;
		}

		this->eventManager->initEvents();
		this->eventManager->initSharedData();

		libThread = (HANDLE)_beginthreadex(NULL, 0, &Library::libThreadFunc, this, 0, NULL);
		if (libThread == NULL) {
			showError("�� ���������� ������� ����� ��������������.");

			// STUB
			// ������� ����� �� ����������?
			//exit(eecFailToBeginLibThread);
			return;
		}
	}

	// ��������� ������ ����������. ���������� ������ ��� ��� ���������� ���������.
	void Library::StopLibThread()
	{
		if (libThread == NULL)
			return;

		// �������� ������ ����������, ��� ����� ��������� ������
		this->eventManager->shutdown();
		// ��� ���������� ������������� ������
		waitForSingle(libThread);
		// ��������� ����� ������������� ������
		freeHandle(libThread);
		libThread = NULL;

		this->eventManager->freeEvents();
		this->eventManager->freeSharedData();
	}
	
	// �������� ������� ������ ����������. ���������� ������ ��� �� ���� ��������� ���� ���������.
	unsigned int Library::libThreadFunc(void* pvParam)
	{
		// ��������� ��������� �� listener
		// STUB ��� ��� ����?
		//listener = (QnApplicationListener*) pvParam;
	
		// ��� ������� ���������� QSP (QSPInit � �.�.) 
		// ���������� ������ ������ ������ ����������.

		// �������������� ����������
		QSPInit();
	
		// ����������� �������
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
		// �����������, ������ �� ���������� ��������� QSP_CALL_PLAYERINFO.
		// ������������ ���������? �� �� �����?
		//QSPSetCallBack(QSP_CALL_PLAYERINFO, (QSP_CALLBACK)&PlayerInfo);

		//QSPSetCallBack(QSP_CALL_SHOWIMAGE, (QSP_CALLBACK)&ShowPicture);
		//QSPSetCallBack(QSP_CALL_SHOWWINDOW, (QSP_CALLBACK)&ShowWindow);
		//QSPSetCallBack(QSP_CALL_SYSTEM, (QSP_CALLBACK)&System);
		//QSPSetCallBack(QSP_CALL_OPENGAMESTATUS, (QSP_CALLBACK)&OpenGameStatus);
		//QSPSetCallBack(QSP_CALL_SAVEGAMESTATUS, (QSP_CALLBACK)&SaveGameStatus);
	
		// ��������� �������� �� ��������� ��� �����
		Skin::initDefaults();
	
		// ���� ��� ���������� ������
		bool bShutdown = false;
	
		// ��������� ������ Audiere ��� ������������ �������� ������
		if (!SoundManager::init()) {
			bShutdown = true;
		}
	
		// ��������� ������� ���������� � �����
		while (!bShutdown) {
			// �������� ������ UI, ��� ���������� ������ � ���������� ������
			runSyncEvent(evLibIsReady);
			// ������� ����� �� ������� �������������
			DWORD res = WaitForMultipleObjects((DWORD)evLastUi, g_eventList, FALSE, INFINITE);
			if ((res < WAIT_OBJECT_0) || (res > (WAIT_OBJECT_0 + evLast - 1))) {
				showError("�� ������� ��������� �������������� ������� ������������� ����������.");
				bShutdown = true;
			} else {
				eSyncEvent ev = (eSyncEvent)res;
				switch (ev)
				{
				case evRunGame:
					{
						// ������ ����
						string path = "";
						int isStandalone = 0;
						lockData();
						path = g_sharedData[evRunGame].str;
						isStandalone = g_sharedData[evRunGame].num;
						unlockData();
						QSP_BOOL res = QSPLoadGameWorld(widen(path).c_str());
						CheckQspResult(res, "QSPLoadGameWorld");
						// ������� ����
						Skin::resetUpdate();
						Skin::resetSettings();
						// ������� ��������� �� ������� � ����.
						Skin::setInt(espIsStandalone, isStandalone);
						// ������� ����� JS-������, ������������ �� ����
						jsExecBuffer = "";
	
						// ������������� ������ ���������� � ��������� ������
						SetTimer(500);
	
						//��������� ������� �����������
						gameStartTime = clock();
	
						res = QSPRestartGame(QSP_TRUE);
						CheckQspResult(res, "QSPRestartGame");
					}
					break;
				case evStopGame:
					{
						// ��������� ����
	
						// ������������� ������.
						stopTimer();
	
						//������������� ������
						CloseFile(NULL);
	
						// ������� ����� JS-������, ������������ �� ����
						jsExecBuffer = "";
	
						runSyncEvent(evGameStopped);
					}
					break;
				case evShutdown:
					{
						// ���������� ������
						bShutdown = true;
					}
					break;
				case evExecuteCode:
					{
						// ���������� ������ ����
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
						// ���������� ��������
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
						// ����� ��������
						int pos = 0;
						lockData();
						pos = g_sharedData[evSelectObject].num;
						unlockData();
						// ������� - ������ �� ������� ���������� ��������,
						// ��� ��� ����� ���������� ����� ��������
						// ���� ��������� ��� ������ UNSEL � ONOBJSEL.
						// ����� ��������� ��� � ���������� QSP.
						objectSelectionIndex = -2;
						QSP_BOOL res = QSPSetSelObjectIndex(pos, QSP_TRUE);
						CheckQspResult(res, "QSPSetSelObjectIndex");
					}
					break;
				case evTimer:
					{
						// ������
						QSP_BOOL res = QSPExecCounter(QSP_TRUE);
						CheckQspResult(res, "QSPExecCounter");
					}
					break;
				case evMute:
					{
						// ��������� / ���������� �����
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
							showError("�� ������ ���� ����������");
							break;
						}
	
						// ��������� ������
						CloseFile(NULL);
	
						// ��������� ����������
						QSP_BOOL res = QSPOpenSavedGame(widen(path).c_str(), QSP_TRUE);
						CheckQspResult(res, "QSPOpenSavedGame");
	
						// ��������� ������
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
							showError("�� ������� ������� ����� ��� ����������: " + saveDir);
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
						// ��������� ����� � ������ �����
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
						showError("�������������� ������� �������������!");
					}
					break;
				}
			}
		}
	
		// ������������� �������� ������
		SoundManager::close(true, "");
		SoundManager::deinit();
	
		// ��������� ������ ����������
		QSPDeInit();
		// ��������� ������ ������
		_endthreadex(0);
		return 0;
	}
}