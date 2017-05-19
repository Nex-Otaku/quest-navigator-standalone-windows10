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
	// ���������� ����������
	// ********************************************************************
	
	//QnApplicationListener* QnApplicationListener::listener = NULL;

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
		// ��������� ��������� �� ������ Library.
		Library* library = (Library*)pvParam;
	
		// ��� ������� ���������� QSP (QSPInit � �.�.) 
		// ���������� ������ ������ ������ ����������.

		// �������������� ����������
		QSPInit();
	
		// ����������� �������
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
		// �����������, ������ �� ���������� ��������� QSP_CALL_PLAYERINFO.
		// ������������ ���������? �� �� �����?
		//QSPSetCallBack(QSP_CALL_PLAYERINFO, (QSP_CALLBACK)&PlayerInfo);

		QSPSetCallBack(QSP_CALL_SHOWIMAGE, (QSP_CALLBACK)&LibraryListener::ShowPicture);
		QSPSetCallBack(QSP_CALL_SHOWWINDOW, (QSP_CALLBACK)&LibraryListener::ShowWindow);
		QSPSetCallBack(QSP_CALL_SYSTEM, (QSP_CALLBACK)&LibraryListener::System);
		QSPSetCallBack(QSP_CALL_OPENGAMESTATUS, (QSP_CALLBACK)&LibraryListener::OpenGameStatus);
		QSPSetCallBack(QSP_CALL_SAVEGAMESTATUS, (QSP_CALLBACK)&LibraryListener::SaveGameStatus);
	
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
			library->eventManager->libIsReady();
			// ������� ����� �� ������� �������������
			DWORD res = library->eventManager->waitForAnyEvent();
			if (!library->eventManager->isValidEvent(res)) {
				showError("�� ������� ��������� �������������� ������� ������������� ����������.");
				bShutdown = true;
			} else {
				eSyncEvent ev = (eSyncEvent)res;
				switch (ev)
				{
				case evRunGame:
					{
						// ������ ����
						SharedDataDto dto = library->eventManager->getSharedData(ev);
						string path = dto.str;
						int isStandalone = dto.num;
						QSP_BOOL res = QSPLoadGameWorld(widen(path).c_str());
						CheckQspResult(res, "QSPLoadGameWorld");
						// ������� ����
						Skin::resetUpdate();
						Skin::resetSettings();
						// ������� ��������� �� ������� � ����.
						Skin::setInt(espIsStandalone, isStandalone);
						// ������� ����� JS-������, ������������ �� ����
						LibraryListener::resetJsExecBuffer();
	
						// ������������� ������ ���������� � ��������� ������
						LibraryListener::SetTimer(500);
	
						//��������� ������� �����������
						LibraryListener::resetMsCount();
	
						res = QSPRestartGame(QSP_TRUE);
						CheckQspResult(res, "QSPRestartGame");
					}
					break;
				case evStopGame:
					{
						// ��������� ����
	
						// ������������� ������.
						library->timer->stopTimer();
	
						//������������� ������
						LibraryListener::CloseFile(NULL);
	
						// ������� ����� JS-������, ������������ �� ����
						LibraryListener::resetJsExecBuffer();
	
						library->eventManager->gameStopped();
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
						SharedDataDto dto = library->eventManager->getSharedData(evExecuteCode);
						string code = dto.str;
						wstring wCode = widen(code);
						QSP_BOOL res = QSPExecString(wCode.c_str(), QSP_TRUE);
						CheckQspResult(res, "QSPExecString");
					}
					break;
				case evExecuteAction:
					{
						// ���������� ��������
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
						// ����� ��������
						SharedDataDto dto = library->eventManager->getSharedData(evSelectObject);
						int pos = dto.num;
						// ������� - ������ �� ������� ���������� ��������,
						// ��� ��� ����� ���������� ����� ��������
						// ���� ��������� ��� ������ UNSEL � ONOBJSEL.
						// ����� ��������� ��� � ���������� QSP.
						LibraryListener::setObjectSelectionIndex(-2);
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
						//// ��������� / ���������� �����
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
						//	showError("�� ������ ���� ����������");
						//	break;
						//}
	
						//// ��������� ������
						//CloseFile(NULL);
	
						//// ��������� ����������
						//QSP_BOOL res = QSPOpenSavedGame(widen(path).c_str(), QSP_TRUE);
						//CheckQspResult(res, "QSPOpenSavedGame");
	
						//// ��������� ������
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
						//	showError("�� ������� ������� ����� ��� ����������: " + saveDir);
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
						//// ��������� ����� � ������ �����
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

	// ��������� ������ ���������� �������� � �������� �� ������, ���� ���������.
	void Library::CheckQspResult(QSP_BOOL successfull, string failMsg)
	{
		//�������� ����������
		//if (successfull == QSP_FALSE)
		//{
		//	//�������� ����������
		//	int line = -1;
		//	int actIndex = -1;
		//	string desc = "";
		//	string loc = "";
		//	int errorNum = -1;
		//	QSP_CHAR* pErrorLoc = NULL;
		//	QSPGetLastErrorData(&errorNum, &pErrorLoc, &actIndex, &line);
		//	loc = Skin::applyHtmlFixes(fromQsp(pErrorLoc));
		//	desc = Skin::applyHtmlFixes(fromQsp(QSPGetErrorDesc(errorNum)));
	
		//	// ��������� ����
		//	Skin::updateBaseVars();
		//	Skin::updateMsgDialog();
		//	// ���� ���-�� ����������, �� �������� � ���������
		//	if (Skin::isSomethingChanged())
		//	{
		//		RefreshInt(QSP_TRUE);
		//	}
	
		//	JSObject jsErrorContainer;
		//	jsErrorContainer.SetProperty(WSLit("desc"), ToWebString(desc));
		//	jsErrorContainer.SetProperty(WSLit("loc"), ToWebString(loc));
		//	jsErrorContainer.SetProperty(WSLit("actIndex"), JSValue(actIndex));
		//	jsErrorContainer.SetProperty(WSLit("line"), JSValue(line));
	
		//	// ������� ������ � ����� UI
		//	qspError(jsErrorContainer);
	
		//	// ��� �������� �������
		//	waitForSingleLib(evErrorClosed);
		//}
	}
}