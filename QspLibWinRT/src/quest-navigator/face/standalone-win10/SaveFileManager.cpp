#include "pch.h"
#include "SaveFileManager.h"
#include <string>
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "..\..\core\files.h"
#include "..\..\core\encoding.h"
#include "..\..\core\configuration.h"
#include "..\..\core\dialogs.h"
#include "Constants.h"

using namespace std;

namespace QuestNavigator {
	SaveFileManager::SaveFileManager()
	{
	}

	SaveFileManager::~SaveFileManager()
	{
	}

	void SaveFileManager::inject(
		Library* library,
		FileSystemManager* fileSystemManager
	)
	{
		this->library = library;
		this->fileSystemManager = fileSystemManager;
	}

	bool SaveFileManager::readSaveFile(string relativePath, bool refresh)
	{
		string saveFile = getFullSavePath(relativePath);
		if (!fileExists(saveFile)) {
			showError("Не найден файл сохранения");
			return false;
		}
		QSP_BOOL isRefresh = refresh ? QSP_TRUE : QSP_FALSE;
		QSP_BOOL res = QSPOpenSavedGame(widen(saveFile).c_str(), isRefresh);
		library->CheckQspResult(res, "QSPOpenSavedGame");
		return res == QSP_TRUE;
	}

	bool SaveFileManager::writeSaveFile(string relativePath)
	{
		string saveDir = Configuration::getString(ecpSaveDir);
		if (!fileSystemManager->directoryExists(saveDir) && !fileSystemManager->buildDirectoryPath(saveDir)) {
			showError("Не удалось создать папку для сохранения: " + saveDir);
			return false;
		}
		string saveFile = getFullSavePath(relativePath);
		QSP_BOOL res = QSPSaveGame(widen(saveFile).c_str(), QSP_FALSE);
		library->CheckQspResult(res, "QSPSaveGame");
		return res == QSP_TRUE;
	}

	SaveSlotsDto SaveFileManager::getSaveSlots(bool open)
	{
		//Контекст UI
		SaveSlotsDto dto;
		vector<string> slots;

		int maxSlots = Configuration::getInt(ecpSaveSlotMax);
		for (int i = 0; i < maxSlots; i++)
		{
			string title;
			string slotname = to_string(i + 1) + ".sav";
			string slotpath = getFullSavePath(slotname);
			if (fileExists(slotpath)) {
				title = to_string(i + 1);
			}
			else {
				title = "-empty-";
			}

			slots.push_back(title);
		}

		dto.open = open;
		dto.slots = slots;

		return dto;
	}

	string SaveFileManager::getFullSavePath(string relativePath)
	{

		//// "D:\MySaveDirForCoolGame"
		//string saveDir = Configuration::getString(ecpSaveDir);
		//// "D:\CoolGame\saves\save1.sav"
		//string originalSaveFilePath = getRightPath(file);
		//// "D:\CoolGame\game.qsp"
		//string gameFilePath = getRightPath(Configuration::getString(ecpGameFilePath));
		//// "game.qsp"
		//string gameFileName = Configuration::getString(ecpGameFileName);
		//// "D:\CoolGame\"
		//string gameDir = gameFilePath.substr(0, gameFilePath.length() - gameFileName.length());
		//// "saves\save1.sav"
		//string relativeSavePath = originalSaveFilePath.substr(gameDir.length());
		//// "D:\MySaveDirForCoolGame\saves\save1.sav"
		//string saveFile = getRightPath(saveDir + PATH_DELIMITER + relativeSavePath);
		//return saveFile;


		string saveDir = Configuration::getString(ecpSaveDir);
		string path = getRightPath(saveDir + PATH_DELIMITER + relativePath);
		return path;
	}
}