#include "pch.h"
#include "LibraryListener.h"

namespace QuestNavigator
{
	LibraryListener::LibraryListener()
	{
	}

	LibraryListener::~LibraryListener()
	{
	}

	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	//                       Колбэки интерпретатора
	// ********************************************************************
	// ********************************************************************
	// ********************************************************************
	
	void LibraryListener::RefreshInt(int isRedraw) 
	{
	//		//Контекст библиотеки
	//		bool needUpdate = Skin::isSomethingChanged();
	//		Skin::updateBaseVars();
	//		needUpdate = needUpdate || Skin::isSomethingChanged();
	//		Skin::updateMainScreen();
	//		needUpdate = needUpdate || Skin::isSomethingChanged();
	//
	//		JSObject jsSkin;
	//		bool bSkinPrepared = false;
	//		if (needUpdate) {
	//			jsSkin = Skin::getJsSkin();
	//			bSkinPrepared = true;
	//		}
	//
	//		//основное описание
	//		string mainDesc = "";
	//		bool bMainDescPrepared = false;
	//		bool bMainDescNeedScroll = false;
	//		if ((QSPIsMainDescChanged() == QSP_TRUE) || Skin::isHtmlModeChanged)
	//		{
	//			mainDesc = Skin::applyHtmlFixes(fromQsp(QSPGetMainDesc()));
	//			bMainDescNeedScroll = startsWith(mainDesc, lastMainDesc);
	//			lastMainDesc = mainDesc;
	//			bMainDescPrepared = true;
	//		}
	//
	//		//список действий
	//		JSArray acts;
	//		bool bActsPrepared = false;
	//		if ((QSPIsActionsChanged() == QSP_TRUE) || Skin::isHtmlModeChanged)
	//		{
	//			int nActsCount = QSPGetActionsCount();
	//			for (int i = 0; i < nActsCount; i++)
	//			{
	//				QSP_CHAR* pImgPath;
	//				QSP_CHAR* pDesc;
	//				QSPGetActionData(i, &pImgPath, &pDesc);
	//				JSObject act;
	//				string imgPath = getRightPath(fromQsp(pImgPath));
	//				string desc = Skin::applyHtmlFixes(fromQsp(pDesc));
	//				act.SetProperty(WSLit("image"), ToWebString(imgPath));
	//				act.SetProperty(WSLit("desc"), ToWebString(desc));
	//				acts.Push(act);
	//			}
	//			bActsPrepared = true;
	//		}
	//
	//		//инвентарь
	//		JSArray objs;
	//		bool bObjsPrepared = false;
	//		int nSelectedObject = QSPGetSelObjectIndex();
	//		if ((QSPIsObjectsChanged() == QSP_TRUE) || (nSelectedObject != objectSelectionIndex) || Skin::isHtmlModeChanged)
	//		{
	//			objectSelectionIndex = nSelectedObject;
	//			int nObjsCount = QSPGetObjectsCount();
	//			for (int i = 0; i < nObjsCount; i++)
	//			{
	//				QSP_CHAR* pImgPath;
	//				QSP_CHAR* pDesc;
	//				QSPGetObjectData(i, &pImgPath, &pDesc);
	//				JSObject obj;
	//				string imgPath = getRightPath(fromQsp(pImgPath));
	//				string desc = Skin::applyHtmlFixes(fromQsp(pDesc));
	//				int selected = (i == nSelectedObject) ? 1 : 0;
	//				obj.SetProperty(WSLit("image"), ToWebString(imgPath));
	//				obj.SetProperty(WSLit("desc"), ToWebString(desc));
	//				obj.SetProperty(WSLit("selected"), JSValue(selected));
	//				objs.Push(obj);
	//			}
	//			bObjsPrepared = true;
	//		}
	//
	//		//доп. описание
	//		string varsDesc = "";
	//		bool bVarsDescPrepared = false;
	//		if ((QSPIsVarsDescChanged() == QSP_TRUE) || Skin::isHtmlModeChanged)
	//		{
	//			varsDesc = Skin::applyHtmlFixes(fromQsp(QSPGetVarsDesc()));
	//			bVarsDescPrepared = true;
	//		}
	//
	//		// Яваскрипт, переданный из игры командой EXEC('JS:...')
	//		string jsCmd = "";
	//		bool bJsCmdPrepared = false;
	//		if (jsExecBuffer.length() > 0)
	//		{
	//			jsCmd = jsExecBuffer;
	//			jsExecBuffer = "";
	//			bJsCmdPrepared = true;
	//		}
	//
	//		// Передаем собранные данные в яваскрипт
	//		if (bSkinPrepared || bMainDescPrepared || bActsPrepared || bObjsPrepared || bVarsDescPrepared ||
	//			bJsCmdPrepared)
	//		{
	//			JSObject groupedContent;
	//			if (bSkinPrepared)
	//				groupedContent.SetProperty(WSLit("skin"), jsSkin);
	//			if (bMainDescPrepared) {
	//				groupedContent.SetProperty(WSLit("main"), ToWebString(mainDesc));
	//				groupedContent.SetProperty(WSLit("scrollmain"), JSValue(bMainDescNeedScroll ? 1 : 0));
	//			}
	//			if (bActsPrepared)
	//				groupedContent.SetProperty(WSLit("acts"), acts);
	//			if (bVarsDescPrepared)
	//				groupedContent.SetProperty(WSLit("vars"), ToWebString(varsDesc));
	//			if (bObjsPrepared)
	//				groupedContent.SetProperty(WSLit("objs"), objs);
	//			if (bJsCmdPrepared)
	//				groupedContent.SetProperty(WSLit("js"), ToWebString(jsCmd));
	//			qspSetGroupedContent(groupedContent);
	//		}
	//		Skin::resetUpdate();
	}
	
	void LibraryListener::SetTimer(int msecs)
	{
	//		//Контекст библиотеки
	//		timerInterval = msecs;
	//		startTimer();
	}
	
	void LibraryListener::SetInputStrText(QSP_CHAR* text)
	{
	//		//Контекст библиотеки
	//		qspSetInputString(ToWebString(fromQsp(text)));
	}
	
	void LibraryListener::ShowMessage(QSP_CHAR* message)
	{
	//		//Контекст библиотеки
	//
	//		// Обновляем скин
	//		Skin::updateBaseVars();
	//		Skin::updateMsgDialog();
	//		// Если что-то изменилось, то передаем в яваскрипт
	//		if (Skin::isSomethingChanged())
	//		{
	//			RefreshInt(QSP_TRUE);
	//		}
	//
	//		string msgValue = Skin::applyHtmlFixes(fromQsp(message));
	//
	//		// Передаём данные в поток UI
	//		qspMsg(ToWebString(msgValue));
	//
	//		// Ждём закрытия диалога
	//		waitForSingleLib(evMsgClosed);
	}
	
	void LibraryListener::PlayFile(QSP_CHAR* file, int volume)
	{
	//		//Контекст библиотеки
	//		string fileName = fromQsp(file);
	//		SoundManager::play(fileName, volume);
	}
	
	QSP_BOOL LibraryListener::IsPlayingFile(QSP_CHAR* file)
	{
	//		//Контекст библиотеки
	//		bool isPlaying = SoundManager::isPlaying(fromQsp(file));
	//		return isPlaying ? QSP_TRUE : QSP_FALSE;
	}
	
	void LibraryListener::CloseFile(QSP_CHAR* file)
	{
	//		//Контекст библиотеки
	//		bool closeAll = file == NULL;
	//		SoundManager::close(closeAll, fromQsp(file));
	}
	
	void LibraryListener::ShowPicture(QSP_CHAR* file)
	{
	//		//Контекст библиотеки
	//		string fileName = getRightPath(fromQsp(file));
	//
	//		// Проверяем читаемость файла.
	//		// Если файл не существует или не читается, выходим.
	//		if (fileName.length() > 0) {
	//			if (!fileExists(fileName)) {
	//				showError("Оператор VIEW. Не найден файл: " + fileName);
	//				return;
	//			}
	//		}
	//
	//		// "Пустое" имя файла тоже имеет значение - так мы скрываем картинку
	//		qspView(ToWebString(fileName));
	}
	
	void LibraryListener::InputBox(const QSP_CHAR* prompt, QSP_CHAR* buffer, int maxLen)
	{
	//		//Контекст библиотеки
	//
	//		// Обновляем скин
	//		Skin::updateBaseVars();
	//		Skin::updateInputDialog();
	//		// Если что-то изменилось, то передаем в яваскрипт
	//		if (Skin::isSomethingChanged())
	//		{
	//			RefreshInt(QSP_TRUE);
	//		}
	//
	//		string promptValue = fromQsp(prompt);
	//
	//		// Передаём данные в поток UI
	//		qspInput(ToWebString(promptValue));
	//
	//		// Ждём закрытия диалога
	//		waitForSingleLib(evInputClosed);
	//
	//		// Возвращаем результат в библиотеку
	//		string result = "";
	//		lockData();
	//		result = g_sharedData[evInputClosed].str;
	//		unlockData();
	//		wstring wResult = widen(result);
	//		wcsncpy(buffer, wResult.c_str(), maxLen);
	}
	
	
	// Функция запросов к плееру.
	// С помощью этой функции мы можем в игре узнать параметры окружения плеера.
	// Вызывается так: $platform = GETPLAYER('platform')
	// @param resource
	// @return
	
	void LibraryListener::PlayerInfo(QSP_CHAR* resource, QSP_CHAR* buffer, int maxLen)
	{
	//		//Контекст библиотеки
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
	//		// Возвращаем результат в библиотеку
	//		wstring wResult = widen(result);
	//		wcsncpy(buffer, wResult.c_str(), maxLen);
	}
	
	int LibraryListener::GetMSCount()
	{
	//		//Контекст библиотеки
	//		clock_t now = clock();
	//		int elapsed = (int) (((now - gameStartTime) * 1000) / CLOCKS_PER_SEC);
	//		gameStartTime = now;
	//		return elapsed;
	}
	
	void LibraryListener::AddMenuItem(QSP_CHAR* name, QSP_CHAR* imgPath)
	{
	//		//Контекст библиотеки
	//		ContainerMenuItem item;
	//		item.imgPath = getRightPath(fromQsp(imgPath));
	//		item.name = fromQsp(name);
	//		menuList.push_back(item);
	}
	
	int LibraryListener::ShowMenu()
	{
	//		//Контекст библиотеки
	//
	//		JSArray jsMenuList;
	//		for (int i = 0; i < (int)menuList.size(); i++) {
	//			JSObject jsMenuItem;
	//			jsMenuItem.SetProperty(WSLit("image"), ToWebString(menuList[i].imgPath));
	//			jsMenuItem.SetProperty(WSLit("desc"), ToWebString(Skin::applyHtmlFixes(menuList[i].name)));
	//			jsMenuList.Push(jsMenuItem);
	//		}
	//
	//		// Передаём данные в поток UI
	//		qspMenu(jsMenuList);
	//
	//		// Ждём закрытия диалога
	//		waitForSingleLib(evMenuClosed);
	//
	//		// Возвращаем результат
	//		int result = -1;
	//		lockData();
	//		result = g_sharedData[evMenuClosed].num;
	//		unlockData();
	//
	//		return result;
	}
	
	void LibraryListener::DeleteMenu()
	{
	//		//Контекст библиотеки
	//		menuList.clear();
	}
	
	void LibraryListener::Wait(int msecs)
	{
	//		//Контекст библиотеки
	//		Sleep((DWORD)msecs);
	}
	
	void LibraryListener::ShowWindow(int type, QSP_BOOL isShow)
	{
	//		// Контекст библиотеки
	//		Skin::showWindow(type, isShow);
	}
	
	void LibraryListener::System(QSP_CHAR* cmd)
	{
	//		//Контекст библиотеки
	//		string jsCmd = fromQsp(cmd);
	//		string jsCmdUpper = toUpper(jsCmd);
	//		if (startsWith(jsCmdUpper, "JS:"))
	//		{
	//			jsCmd = jsCmd.substr(string("JS:").length());
	//			// Сохраняем яваскрипт, переданный из игры командой EXEC('JS:...')
	//			// На выполнение отдаём при обновлении интерфейса
	//			jsExecBuffer = jsExecBuffer + jsCmd;
	//		}
	}
	
	void LibraryListener::OpenGameStatus(QSP_CHAR* file)
	{
	//		//Контекст библиотеки
	//		if (file != 0) {
	//			// Библиотека возвращает абсолютный путь к файлу сохранения,
	//			// вычисляемый по пути к файлу игры.
	//			// Таким образом, если игра запущена из пути "D:\CoolGame\game.qsp",
	//			// то при выполнении команды 
	//			// OPENGAME 'saves\save1.sav'
	//			// сейв будет загружаться из папки игры:
	//			// "D:\CoolGame\saves\save1.sav"
	//			// Нас это не устраивает, 
	//			// нам нужно, чтобы сейвы хранились в отдельном безопасном месте.
	//			// Поэтому мы меняем путь, заданный библиотекой, на свой.
	//			string saveFile = getRealSaveFile(fromQsp(file));
	//			if (fileExists(saveFile)) {
	//				QSP_BOOL res = QSPOpenSavedGame(widen(saveFile).c_str(), QSP_FALSE);
	//				CheckQspResult(res, "QSPOpenSavedGame");
	//			}
	//		} else {
	//			jsExecBuffer = jsExecBuffer + ";qspLoadGame();";
	//		}
	}
	
	void LibraryListener::SaveGameStatus(QSP_CHAR* file)
	{
	//		//Контекст библиотеки
	//		if (file != 0) {
	//			string saveDir = Configuration::getString(ecpSaveDir);
	//			if (!dirExists(saveDir) && !buildDirectoryPath(saveDir)) {
	//				showError("Не удалось создать папку для сохранения: " + saveDir);
	//				return;
	//			}
	//			// Библиотека возвращает абсолютный путь к файлу сохранения,
	//			// вычисляемый по пути к файлу игры.
	//			// Таким образом, если игра запущена из пути "D:\CoolGame\game.qsp",
	//			// то при выполнении команды 
	//			// SAVEGAME 'saves\save1.sav'
	//			// сейв будет сохраняться в папке игры:
	//			// "D:\CoolGame\saves\save1.sav"
	//			// Нас это не устраивает, 
	//			// нам нужно, чтобы сейвы хранились в отдельном безопасном месте.
	//			// Поэтому мы меняем путь, заданный библиотекой, на свой.
	//			string saveFile = getRealSaveFile(fromQsp(file));
	//			QSP_BOOL res = QSPSaveGame(widen(saveFile).c_str(), QSP_FALSE);
	//			CheckQspResult(res, "QSPSaveGame");
	//		} else {
	//			jsExecBuffer = jsExecBuffer + ";qspSaveGame();";
	//		}
	}
}