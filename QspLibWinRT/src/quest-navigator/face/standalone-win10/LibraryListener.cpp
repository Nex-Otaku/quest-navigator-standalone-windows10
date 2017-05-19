#include "pch.h"
#include "LibraryListener.h"
#include <string>
#include "..\..\core\skin.h"
#include "..\..\core\dto\SkinDto.h"
#include "..\..\core\strings.h"
#include "..\..\core\encoding.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\files.h"
#include "JsExecutor.h"
#include "..\..\core\sound.h"
#include "Timer.h"
#include "EventManager.h"
#include "..\..\core\dialogs.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "Library.h"

namespace QuestNavigator
{
	LibraryListener* LibraryListener::instance()
	{
		static LibraryListener inst;
		return &inst;
	}

	void LibraryListener::inject(
		JsExecutor* jsExecutor,
		Timer* timer,
		EventManager* eventManager
	)
	{
		this->jsExecutor = jsExecutor;
		this->timer = timer;
		this->eventManager = eventManager;
	}

	LibraryListener::LibraryListener()
	{
	}

	LibraryListener::~LibraryListener()
	{
	}

	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	//                       ������� ��������������
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	
	string LibraryListener::jsExecBuffer = "";
	string LibraryListener::lastMainDesc = "";
	int LibraryListener::objectSelectionIndex = -2;
	clock_t LibraryListener::gameStartTime = 0;
	vector<MenuItemDto> LibraryListener::menuList;

	void LibraryListener::RefreshInt(int isRedraw)
	{
		//�������� ����������
		bool needUpdate = Skin::isSomethingChanged();
		Skin::updateBaseVars();
		needUpdate = needUpdate || Skin::isSomethingChanged();
		Skin::updateMainScreen();
		needUpdate = needUpdate || Skin::isSomethingChanged();
	
		GroupedContentDto groupedContent;
		bool bSkinPrepared = false;
		if (needUpdate) {
			SkinDto jsSkin = Skin::getJsSkin();
			groupedContent.skin = jsSkin;
			bSkinPrepared = true;
		}

		//�������� ��������
		bool bMainDescPrepared = false;
		bool bMainDescNeedScroll = false;
		if ((QSPIsMainDescChanged() == QSP_TRUE) || Skin::isHtmlModeChanged)
		{
			string mainDesc = Skin::applyHtmlFixes(fromQsp(QSPGetMainDesc()));
			bMainDescNeedScroll = startsWith(mainDesc, lastMainDesc);
			lastMainDesc = mainDesc;
			groupedContent.main = mainDesc;
			groupedContent.scrollmain = bMainDescNeedScroll ? 1 : 0;
			bMainDescPrepared = true;
		}
	
		//������ ��������
		vector<GroupedContentDto::act> acts;
		bool bActsPrepared = false;
		if ((QSPIsActionsChanged() == QSP_TRUE) || Skin::isHtmlModeChanged)
		{
			int nActsCount = QSPGetActionsCount();
			for (int i = 0; i < nActsCount; i++)
			{
				QSP_CHAR* pImgPath;
				QSP_CHAR* pDesc;
				QSPGetActionData(i, &pImgPath, &pDesc);
				GroupedContentDto::act act;
				string imgPath = getRightPath(fromQsp(pImgPath));
				string desc = Skin::applyHtmlFixes(fromQsp(pDesc));
				act.image = imgPath;
				act.desc = desc;
				acts.push_back(act);
			}
			groupedContent.acts = acts;
			bActsPrepared = true;
		}
	
		//���������
		vector<GroupedContentDto::obj> objs;
		bool bObjsPrepared = false;
		int nSelectedObject = QSPGetSelObjectIndex();
		if ((QSPIsObjectsChanged() == QSP_TRUE) || (nSelectedObject != objectSelectionIndex) || Skin::isHtmlModeChanged)
		{
			objectSelectionIndex = nSelectedObject;
			int nObjsCount = QSPGetObjectsCount();
			for (int i = 0; i < nObjsCount; i++)
			{
				QSP_CHAR* pImgPath;
				QSP_CHAR* pDesc;
				QSPGetObjectData(i, &pImgPath, &pDesc);
				GroupedContentDto::obj obj;
				string imgPath = getRightPath(fromQsp(pImgPath));
				string desc = Skin::applyHtmlFixes(fromQsp(pDesc));
				int selected = (i == nSelectedObject) ? 1 : 0;
				obj.image = imgPath;
				obj.desc = desc;
				obj.selected = selected;
				objs.push_back(obj);
			}
			groupedContent.objs = objs;
			bObjsPrepared = true;
		}
	
		//���. ��������
		bool bVarsDescPrepared = false;
		if ((QSPIsVarsDescChanged() == QSP_TRUE) || Skin::isHtmlModeChanged)
		{
			groupedContent.vars = Skin::applyHtmlFixes(fromQsp(QSPGetVarsDesc()));
			bVarsDescPrepared = true;
		}
	
		// ���������, ���������� �� ���� �������� EXEC('JS:...')
		bool bJsCmdPrepared = false;
		if (jsExecBuffer.length() > 0)
		{
			groupedContent.js = jsExecBuffer;
			jsExecBuffer = "";
			bJsCmdPrepared = true;
		}
	
		// �������� ��������� ������ � ���������
		if (bSkinPrepared || bMainDescPrepared || bActsPrepared || bObjsPrepared || bVarsDescPrepared ||
			bJsCmdPrepared)
		{
			instance()->jsExecutor->qspSetGroupedContent(groupedContent);
		}
		Skin::resetUpdate();
	}
	
	void LibraryListener::SetTimer(int msecs)
	{
		//�������� ����������
		instance()->timer->setTimerInterval(msecs);
		instance()->timer->startTimer();
	}
	
	void LibraryListener::SetInputStrText(QSP_CHAR* text)
	{
		//�������� ����������
		instance()->jsExecutor->qspSetInputString(fromQsp(text));
	}
	
	void LibraryListener::ShowMessage(QSP_CHAR* message)
	{
		//�������� ����������
	
		// ��������� ����
		Skin::updateBaseVars();
		Skin::updateMsgDialog();
		// ���� ���-�� ����������, �� �������� � ���������
		if (Skin::isSomethingChanged())
		{
			RefreshInt(QSP_TRUE);
		}
	
		string msgValue = Skin::applyHtmlFixes(fromQsp(message));
	
		// ������� ������ � ����� UI
		instance()->jsExecutor->qspMsg(msgValue);
	
		// ��� �������� �������
		instance()->eventManager->waitForMsgClosed();
	}
	
	void LibraryListener::PlayFile(QSP_CHAR* file, int volume)
	{
		//�������� ����������
		string fileName = fromQsp(file);
		SoundManager::play(fileName, volume);
	}
	
	QSP_BOOL LibraryListener::IsPlayingFile(QSP_CHAR* file)
	{
		//�������� ����������
		bool isPlaying = SoundManager::isPlaying(fromQsp(file));
		return isPlaying ? QSP_TRUE : QSP_FALSE;
	}
	
	void LibraryListener::CloseFile(QSP_CHAR* file)
	{
		//�������� ����������
		bool closeAll = file == NULL;
		SoundManager::close(closeAll, fromQsp(file));
	}
	
	void LibraryListener::ShowPicture(QSP_CHAR* file)
	{
		//�������� ����������
		string fileName = getRightPath(fromQsp(file));
	
		// ��������� ���������� �����.
		// ���� ���� �� ���������� ��� �� ��������, �������.
		if (fileName.length() > 0) {
			if (!fileExists(fileName)) {
				showError("�������� VIEW. �� ������ ����: " + fileName);
				return;
			}
		}
	
		// "������" ��� ����� ���� ����� �������� - ��� �� �������� ��������
		instance()->jsExecutor->qspView(fileName);
	}
	
	void LibraryListener::InputBox(const QSP_CHAR* prompt, QSP_CHAR* buffer, int maxLen)
	{
		//�������� ����������
	
		// ��������� ����
		Skin::updateBaseVars();
		Skin::updateInputDialog();
		// ���� ���-�� ����������, �� �������� � ���������
		if (Skin::isSomethingChanged())
		{
			RefreshInt(QSP_TRUE);
		}
	
		string promptValue = fromQsp(prompt);
	
		// ������� ������ � ����� UI
		instance()->jsExecutor->qspInput(promptValue);
	
		// ��� �������� �������
		instance()->eventManager->waitForInputClosed();
	
		// ���������� ��������� � ����������
		SharedDataDto dto = instance()->eventManager->getSharedData(evInputClosed);
		string result = dto.str;
		wstring wResult = widen(result);
		wcsncpy(buffer, wResult.c_str(), maxLen);
	}
	
	
	// ������� �������� � ������.
	// � ������� ���� ������� �� ����� � ���� ������ ��������� ��������� ������.
	// ���������� ���: $platform = GETPLAYER('platform')
	// @param resource
	// @return
	
	void LibraryListener::PlayerInfo(QSP_CHAR* resource, QSP_CHAR* buffer, int maxLen)
	{
	//		//�������� ����������
	//		string resourceName = fromQsp(resource);
	//		resourceName = toLower(resourceName);
	//		string result = "";
	//		if (resourceName == "platform") {
	//			result = "Windows";
	//		} else if (resourceName == "player") {
	//			result = QN_APP_NAME;
	//		} else if (resourceName == "player.version") {
	//			result = QN_VERSION;
	//		}
	//
	//		// ���������� ��������� � ����������
	//		wstring wResult = widen(result);
	//		wcsncpy(buffer, wResult.c_str(), maxLen);
	}

	// ���������� ���������� �����������, 
	// ��������� � ������� ���������� ������ ���� �������.
	int LibraryListener::GetMSCount()
	{
		//�������� ����������
		clock_t now = clock();
		int elapsed = (int) (((now - gameStartTime) * 1000) / CLOCKS_PER_SEC);
		gameStartTime = now;
		return elapsed;
	}
	
	void LibraryListener::AddMenuItem(QSP_CHAR* name, QSP_CHAR* imgPath)
	{
		//�������� ����������
		MenuItemDto item;
		item.image = getRightPath(fromQsp(imgPath));
		item.desc = fromQsp(name);
		menuList.push_back(item);
	}
	
	int LibraryListener::ShowMenu()
	{
		//�������� ����������

		// ��������� ������ ���� � ������ �������� �����.
		vector<MenuItemDto> formattedMenuList;
		for (int i = 0; i < (int)menuList.size(); i++) {
			MenuItemDto item;
			item.image = menuList[i].image;
			item.desc = Skin::applyHtmlFixes(menuList[i].desc);
			formattedMenuList.push_back(item);
		}
	
		// ������� ������ � ����� UI
		instance()->jsExecutor->qspMenu(formattedMenuList);
	
		// ��� �������� �������
		instance()->eventManager->waitForMenuClosed();
	
		// ���������� ���������
		SharedDataDto dto = instance()->eventManager->getSharedData(evMenuClosed);
		int result = dto.num;
	
		return result;
	}
	
	void LibraryListener::DeleteMenu()
	{
		//�������� ����������
		menuList.clear();
	}
	
	void LibraryListener::Wait(int msecs)
	{
		//�������� ����������
		Sleep((DWORD)msecs);
	}
	
	void LibraryListener::ShowWindow(int type, QSP_BOOL isShow)
	{
		// �������� ����������
		Skin::showWindow(type, isShow);
	}
	
	void LibraryListener::System(QSP_CHAR* cmd)
	{
		//�������� ����������
		string jsCmd = fromQsp(cmd);
		string jsCmdUpper = toUpper(jsCmd);
		if (startsWith(jsCmdUpper, "JS:"))
		{
			jsCmd = jsCmd.substr(string("JS:").length());
			// ��������� ���������, ���������� �� ���� �������� EXEC('JS:...')
			// �� ���������� ����� ��� ���������� ����������
			jsExecBuffer = jsExecBuffer + jsCmd;
		}
	}
	
	void LibraryListener::OpenGameStatus(QSP_CHAR* file)
	{
		//�������� ����������
		if (file != 0) {
			// ���������� ���������� ���������� ���� � ����� ����������,
			// ����������� �� ���� � ����� ����.
			// ����� �������, ���� ���� �������� �� ���� "D:\CoolGame\game.qsp",
			// �� ��� ���������� ������� 
			// OPENGAME 'saves\save1.sav'
			// ���� ����� ����������� �� ����� ����:
			// "D:\CoolGame\saves\save1.sav"
			// ��� ��� �� ����������, 
			// ��� �����, ����� ����� ��������� � ��������� ���������� �����.
			// ������� �� ������ ����, �������� �����������, �� ����.
			string saveFile = getRealSaveFile(fromQsp(file));
			if (fileExists(saveFile)) {
				QSP_BOOL res = QSPOpenSavedGame(widen(saveFile).c_str(), QSP_FALSE);
				Library::CheckQspResult(res, "QSPOpenSavedGame");
			}
		} else {
			jsExecBuffer = jsExecBuffer + ";qspLoadGame();";
		}
	}
	
	void LibraryListener::SaveGameStatus(QSP_CHAR* file)
	{
		//�������� ����������
		if (file != 0) {
			string saveDir = Configuration::getString(ecpSaveDir);
			if (!dirExists(saveDir) && !buildDirectoryPath(saveDir)) {
				showError("�� ������� ������� ����� ��� ����������: " + saveDir);
				return;
			}
			// ���������� ���������� ���������� ���� � ����� ����������,
			// ����������� �� ���� � ����� ����.
			// ����� �������, ���� ���� �������� �� ���� "D:\CoolGame\game.qsp",
			// �� ��� ���������� ������� 
			// SAVEGAME 'saves\save1.sav'
			// ���� ����� ����������� � ����� ����:
			// "D:\CoolGame\saves\save1.sav"
			// ��� ��� �� ����������, 
			// ��� �����, ����� ����� ��������� � ��������� ���������� �����.
			// ������� �� ������ ����, �������� �����������, �� ����.
			string saveFile = getRealSaveFile(fromQsp(file));
			QSP_BOOL res = QSPSaveGame(widen(saveFile).c_str(), QSP_FALSE);
			Library::CheckQspResult(res, "QSPSaveGame");
		} else {
			jsExecBuffer = jsExecBuffer + ";qspSaveGame();";
		}
	}

	void LibraryListener::resetJsExecBuffer()
	{
		jsExecBuffer = "";
	}

	void LibraryListener::resetMsCount()
	{
		gameStartTime = clock();
	}

	void LibraryListener::setObjectSelectionIndex(int index)
	{
		objectSelectionIndex = index;
	}
}