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
//#include "..\..\core\sound.h"
#include "Timer.h"
#include "EventManager.h"
#include "..\..\core\dialogs.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "Library.h"
#include "Constants.h"
#include "AudioManager.h"

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
		EventManager* eventManager,
		Library* library,
		PathConverter* pathConverter,
		SaveFileManager* saveFileManager,
		AudioManager* audioManager
	)
	{
		this->jsExecutor = jsExecutor;
		this->timer = timer;
		this->eventManager = eventManager;
		this->library = library;
		this->pathConverter = pathConverter;
		this->saveFileManager = saveFileManager;
		this->audioManager = audioManager;
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
	//                       Колбэки интерпретатора
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
		//Контекст библиотеки
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

		//основное описание
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
	
		//список действий
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
	
		//инвентарь
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
	
		//доп. описание
		bool bVarsDescPrepared = false;
		if ((QSPIsVarsDescChanged() == QSP_TRUE) || Skin::isHtmlModeChanged)
		{
			groupedContent.vars = Skin::applyHtmlFixes(fromQsp(QSPGetVarsDesc()));
			bVarsDescPrepared = true;
		}
	
		// Яваскрипт, переданный из игры командой EXEC('JS:...')
		bool bJsCmdPrepared = false;
		if (jsExecBuffer.length() > 0)
		{
			groupedContent.js = jsExecBuffer;
			jsExecBuffer = "";
			bJsCmdPrepared = true;
		}

		// Заполняем флаги.
		groupedContent.skinPrepared = bSkinPrepared;
		groupedContent.mainDescPrepared = bMainDescPrepared;
		groupedContent.actsPrepared = bActsPrepared;
		groupedContent.objsPrepared = bObjsPrepared;
		groupedContent.varsDescPrepared = bVarsDescPrepared;
		groupedContent.jsCmdPrepared = bJsCmdPrepared;

		// Передаем собранные данные в яваскрипт
		if (bSkinPrepared || bMainDescPrepared || bActsPrepared || bObjsPrepared || bVarsDescPrepared ||
			bJsCmdPrepared)
		{
			instance()->jsExecutor->qspSetGroupedContent(groupedContent);
		}
		Skin::resetUpdate();
	}
	
	void LibraryListener::SetTimer(int msecs)
	{
		//Контекст библиотеки
		instance()->timer->setTimerInterval(msecs);
		instance()->timer->startTimer();
	}
	
	void LibraryListener::SetInputStrText(QSP_CHAR* text)
	{
		//Контекст библиотеки
		instance()->jsExecutor->qspSetInputString(fromQsp(text));
	}
	
	void LibraryListener::ShowMessage(QSP_CHAR* message)
	{
		//Контекст библиотеки
	
		// Обновляем скин
		Skin::updateBaseVars();
		Skin::updateMsgDialog();
		// Если что-то изменилось, то передаем в яваскрипт
		if (Skin::isSomethingChanged())
		{
			RefreshInt(QSP_TRUE);
		}
	
		string msgValue = Skin::applyHtmlFixes(fromQsp(message));
	
		// Передаём данные в поток UI
		instance()->jsExecutor->qspMsg(msgValue);
	
		// Ждём закрытия диалога
		instance()->eventManager->waitForMsgClosed();
	}
	
	void LibraryListener::PlayFile(QSP_CHAR* file, int volume)
	{
		//Контекст библиотеки
		string fileName = fromQsp(file);
		//SoundManager::play(fileName, volume);
	}
	
	QSP_BOOL LibraryListener::IsPlayingFile(QSP_CHAR* file)
	{
		//Контекст библиотеки
		//bool isPlaying = SoundManager::isPlaying(fromQsp(file));
		bool isPlaying = false;
		return isPlaying ? QSP_TRUE : QSP_FALSE;
	}
	
	void LibraryListener::CloseFile(QSP_CHAR* file)
	{
		//Контекст библиотеки
		bool closeAll = file == NULL;
		//SoundManager::close(closeAll, fromQsp(file));
	}
	
	void LibraryListener::ShowPicture(QSP_CHAR* file)
	{
		//Контекст библиотеки
		string fileName = getRightPath(fromQsp(file));

		// Проверяем читаемость файла.
		// Если файл не существует или не читается, выходим.
		if (fileName.length() > 0) {
			if (!fileExists(fileName)) {
				showError("Оператор VIEW. Не найден файл: " + fileName);
				return;
			}
			
			// Билиотека возвращает абсолютный путь к файлу.
			// Но для отображения в HTML нам требуется относительный URL.
			fileName = instance()->pathConverter->absolutePathToRelativeUrl(fileName);
		}
	
		// "Пустое" имя файла тоже имеет значение - так мы скрываем картинку
		instance()->jsExecutor->qspView(fileName);
	}
	
	void LibraryListener::InputBox(const QSP_CHAR* prompt, QSP_CHAR* buffer, int maxLen)
	{
		//Контекст библиотеки
	
		// Обновляем скин
		Skin::updateBaseVars();
		Skin::updateInputDialog();
		// Если что-то изменилось, то передаем в яваскрипт
		if (Skin::isSomethingChanged())
		{
			RefreshInt(QSP_TRUE);
		}
	
		string promptValue = fromQsp(prompt);
	
		// Передаём данные в поток UI
		instance()->jsExecutor->qspInput(promptValue);
	
		// Ждём закрытия диалога
		instance()->eventManager->waitForInputClosed();
	
		// Возвращаем результат в библиотеку
		SharedDataDto dto = instance()->eventManager->getSharedData(evInputClosed);
		string result = dto.str;
		wstring wResult = widen(result);
		wcsncpy(buffer, wResult.c_str(), maxLen);
	}
	
	
	// Функция запросов к плееру.
	// С помощью этой функции мы можем в игре узнать параметры окружения плеера.
	// Вызывается так: $platform = GETPLAYER('platform')
	// @param resource
	// @return
	
	void LibraryListener::PlayerInfo(QSP_CHAR* resource, QSP_CHAR* buffer, int maxLen)
	{
		//Контекст библиотеки
		string resourceName = fromQsp(resource);
		resourceName = toLower(resourceName);
		string result = "";
		if (resourceName == "platform") {
			result = "Windows";
		} else if (resourceName == "player") {
			result = QN_APP_NAME;
		} else if (resourceName == "player.version") {
			result = QN_VERSION;
		}
	
		// Возвращаем результат в библиотеку
		wstring wResult = widen(result);
		wcsncpy(buffer, wResult.c_str(), maxLen);
	}

	// Возвращаем количество миллисекунд, 
	// прошедших с момента последнего вызова этой функции.
	int LibraryListener::GetMSCount()
	{
		//Контекст библиотеки
		clock_t now = clock();
		int elapsed = (int) (((now - gameStartTime) * 1000) / CLOCKS_PER_SEC);
		gameStartTime = now;
		return elapsed;
	}
	
	void LibraryListener::AddMenuItem(QSP_CHAR* name, QSP_CHAR* imgPath)
	{
		//Контекст библиотеки
		MenuItemDto item;
		item.image = getRightPath(fromQsp(imgPath));
		item.desc = fromQsp(name);
		menuList.push_back(item);
	}
	
	int LibraryListener::ShowMenu()
	{
		//Контекст библиотеки

		// Формируем список меню с учётом настроек скина.
		vector<MenuItemDto> formattedMenuList;
		for (int i = 0; i < (int)menuList.size(); i++) {
			MenuItemDto item;
			item.image = menuList[i].image;
			item.desc = Skin::applyHtmlFixes(menuList[i].desc);
			formattedMenuList.push_back(item);
		}
	
		// Передаём данные в поток UI
		instance()->jsExecutor->qspMenu(formattedMenuList);
	
		// Ждём закрытия диалога
		instance()->eventManager->waitForMenuClosed();
	
		// Возвращаем результат
		SharedDataDto dto = instance()->eventManager->getSharedData(evMenuClosed);
		int result = dto.num;
	
		return result;
	}
	
	void LibraryListener::DeleteMenu()
	{
		//Контекст библиотеки
		menuList.clear();
	}
	
	void LibraryListener::Wait(int msecs)
	{
		//Контекст библиотеки
		Sleep((DWORD)msecs);
	}
	
	void LibraryListener::ShowWindow(int type, QSP_BOOL isShow)
	{
		// Контекст библиотеки
		Skin::showWindow(type, isShow);
	}
	
	void LibraryListener::System(QSP_CHAR* cmd)
	{
		//Контекст библиотеки
		string jsCmd = fromQsp(cmd);
		string jsCmdUpper = toUpper(jsCmd);
		if (startsWith(jsCmdUpper, "JS:"))
		{
			jsCmd = jsCmd.substr(string("JS:").length());
			// Сохраняем яваскрипт, переданный из игры командой EXEC('JS:...')
			// На выполнение отдаём при обновлении интерфейса
			jsExecBuffer = jsExecBuffer + jsCmd;
		}
	}
	
	void LibraryListener::OpenGameStatus(QSP_CHAR* file)
	{
		//Контекст библиотеки
		if (file != 0) {
			// Библиотека возвращает абсолютный путь к файлу сохранения,
			// вычисляемый по пути к файлу игры.
			// Таким образом, если игра запущена из пути "D:\CoolGame\game.qsp",
			// то при выполнении команды 
			// OPENGAME 'saves\save1.sav'
			// сейв будет загружаться из папки игры:
			// "D:\CoolGame\saves\save1.sav"
			// Нас это не устраивает, 
			// нам нужно, чтобы сейвы хранились в отдельном безопасном месте.
			// Поэтому мы меняем путь, заданный библиотекой, на свой.
			string relativePath = instance()->pathConverter->absolutePathToRelativePath(fromQsp(file));
			instance()->saveFileManager->readSaveFile(relativePath, false);
		} else {
			jsExecBuffer = jsExecBuffer + ";qspLoadGame();";
		}
	}
	
	void LibraryListener::SaveGameStatus(QSP_CHAR* file)
	{
		//Контекст библиотеки
		if (file != 0) {
			// Библиотека возвращает абсолютный путь к файлу сохранения,
			// вычисляемый по пути к файлу игры.
			// Таким образом, если игра запущена из пути "D:\CoolGame\game.qsp",
			// то при выполнении команды 
			// SAVEGAME 'saves\save1.sav'
			// сейв будет сохраняться в папке игры:
			// "D:\CoolGame\saves\save1.sav"
			// Нас это не устраивает, 
			// нам нужно, чтобы сейвы хранились в отдельном безопасном месте.
			// Поэтому мы меняем путь, заданный библиотекой, на свой.
			string relativePath = instance()->pathConverter->absolutePathToRelativePath(fromQsp(file));
			instance()->saveFileManager->writeSaveFile(relativePath);
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