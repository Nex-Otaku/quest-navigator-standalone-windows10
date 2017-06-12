#include "game_files.h"
#include "..\..\face\standalone-win10\Constants.h"
#include "..\..\core\configuration.h"
#include "..\..\core\files.h"
#include "..\..\core\dialogs.h"

namespace QuestNavigator {
	// ������� ���� � �������.
	bool prepareGameFiles()
	{
		// �������� �������� ��������� ������:
		// 1. ���� � ����� ������ ��� � ����� ��������� ��������� ����� 
		//    ���� ����� standalone_content, 
		//    �� �������� ������ ���� ��������� ���,
		//    ����� - �������� ������ ���� ��������� ������ ������ 
		//    ��� ��������� ��������� �����.
		// 2. ��������� ������� � ���������� ����� ����.
		// 3. ��������� ������� ����� "qsplib" ������� ���� �������� ����� ����.
		// 4. ���� ���� ���� ����� � ���� ����� "qsplib", �� ����������� ����.
		// 5. �����, �������� ��������� �����, � ������� ����������:
		// 5.1 - ����� ���������� ���� - .js, .css, ��������;
		// 5.2 - ���� ����� (���� ���� � ����� ���� - �� ���� ����, 
		//                   ����� ��������� ���� ���� �� �����������, 
		//                   ��������� � config.xml)
		// 5.3 - ����� "qsplib".
		// 6. ����������� ���� �� ������ �� ��������� �����.

		// � ������ "standalone" ������ �� ��������, �� ��� ������ ���� �� ����� ������.
		bool bStandalone = Configuration::getBool(ecpGameIsStandalone);

		// ���� ����� ������� �� � ������ standalone,
		// �� ��� ����������� ����� ������.
		string appDataDir = Configuration::getString(ecpAppDataDir);
		// ���� ����� ��� �� ����������, ������.
		if (!bStandalone) {
			if (!buildDirectoryPath(appDataDir)) {
				showError("�� ������� ������� ����� ������ ��� ������: " + appDataDir);
				return false;
			}
		}

		bool bCopyQsplib = false;
		bool bCopySkin = false;
		// ���� ��������� "ContentDir" �� ������, 
		// ������ ���� �� �����.
		// ����� ���������� "����" �� ��������� �� ����� "assets\standalone_content".
		string contentDir = Configuration::getString(ecpContentDir);
		string skinFilePath = Configuration::getString(ecpSkinFilePath);
		string selectedSkin = Configuration::getString(ecpDefaultSkinName);
		string gameFilePath = Configuration::getString(ecpGameFilePath);
		string gameHash = Configuration::getString(ecpGameHash);
		string assetsDir = getPlayerDir() + PATH_DELIMITER + ASSETS_DIR;
		// ��������� ������� qsplib.
		string gameQsplibDir = contentDir + PATH_DELIMITER + ".." + PATH_DELIMITER + QSPLIB_DIR;
		bCopyQsplib = !dirExists(gameQsplibDir);

		// ��������� ������� �����.
		bCopySkin = skinFilePath == "";
		if (bCopySkin) {
			// ��������, ����� ���� ��� ������ ��� ����.
			string configSkin = Configuration::getString(ecpSkinName);
			if (configSkin != "") {
				// �������� ��������� ����.
				selectedSkin = configSkin;
			}
		}

		// ��������� �����������.
		if (bCopyQsplib || bCopySkin) {
			// ���� � ���� ������� ����� "standalone",
			// �� ������� ������ � ��������� ������.
			if (bStandalone) {
				string error = "������: ��� ���������� ������ \"standalone\" ����������� "
					+ (bCopyQsplib ? "����� \"" + QSPLIB_DIR + "\"." : "������ ����������.");
				showError(error);
				return false;
			}

			// ��������� ������� ����� "assets", 
			// ������ ������� ����� ����������� ����� �������� ����������, 
			// "qsplib" � ���� ���� �� ���������.
			if (!dirExists(assetsDir)) {
				showError("�� ������� ����� \"" + assetsDir + "\" ��������� ������ ������.");
				return false;
			}

			// ������ ��������� ����� ��� ����.
			string gameFolder = getRightPath(appDataDir + PATH_DELIMITER + GAME_CACHE_DIR + PATH_DELIMITER + gameHash);
			gameFolder = canonicalizePath(gameFolder);
			if (!buildDirectoryPath(gameFolder)) {
				showError("�� ������� ������� ��������� ����� ��� ����: " + gameFolder);
				return false;
			}
			Configuration::setString(ecpCacheDir, gameFolder);
			string contentFolder = gameFolder + PATH_DELIMITER + DEFAULT_CONTENT_REL_PATH;
			if (!buildDirectoryPath(contentFolder)) {
				showError("�� ������� ������� ����� ��� ����������� ����: " + contentFolder);
				return false;
			}

			// �������� qsplib.
			// true - �� ������� ������, false - �� ����� ����.
			string source = bCopyQsplib ?
				assetsDir + PATH_DELIMITER + QSPLIB_DIR : gameQsplibDir;
			string dest = gameFolder + PATH_DELIMITER + QSPLIB_DIR;
			if (!copyFileTree(source, dest)) {
				showError("�� ������� ����������� ����� ���������� �� \"" + source + "\" � \"" + dest + "\".");
				return false;
			}

			// �������� ����.
			string destSkinFile = contentFolder + PATH_DELIMITER + DEFAULT_SKIN_FILE;
			if (bCopySkin) {
				// �������� �� ������� ������

				string skinsDir = assetsDir + PATH_DELIMITER + SKINS_DIR;

				// ��������� ������ ������������ ������.
				vector<string> skinsList;
				if (!getFoldersList(skinsDir, skinsList))
					return false;

				// ���� ��������� ���� ����� ������������.
				bool found = false;
				for (int i = 0; i < (int)skinsList.size(); i++)
				{
					if (skinsList[i] == selectedSkin) {
						found = true;
						break;
					}
				}

				// ���� �� ������, �������.
				if (!found) {
					showError("�� ������ ������ ���������� " + selectedSkin);
					return false;
				}

				// �������� ��� ����� �� ����� �������
				string source = skinsDir + PATH_DELIMITER + selectedSkin;
				if (!copyFileTree(source, contentFolder)) {
					showError("�� ������� ����������� ������ ���������� �� \"" +
						source + "\" � \"" + contentFolder + "\".");
					return false;
				}
			}
			else {
				// �������� �� ����� ����
				if (!copyFile(skinFilePath, destSkinFile)) {
					showError("�� ������� ����������� ���� ������� ���������� �� \"" +
						skinFilePath + "\" � \"" + destSkinFile + "\".");
					return false;
				}
			}
			// ��������� ���������� ���������
			Configuration::setString(ecpSkinFilePath, destSkinFile);

			// �������� ��� �����, ������� ����� ������������ ��������.
			vector<string> masks;
			// �������� - ".jpg", ".jpeg", ".gif", ".bmp", ".png".
			masks.push_back("*.jpg");
			masks.push_back("*.jpeg");
			masks.push_back("*.gif");
			masks.push_back("*.bmp");
			masks.push_back("*.png");
			masks.push_back("*.cur");
			masks.push_back("*.ani");
			// ����� � ������� - ".css", ".js".
			// ���� bCopySkin == false, ������, �� ���������� ���� �� ����� ����.
			// ������� �������� �� ����� ���� CSS � JS �����.
			if (!bCopySkin) {
				masks.push_back("*.css");
				masks.push_back("*.js");
			}
			// �������� �� ���� �����������.
			for (int i = 0; i < (int)masks.size(); i++) {
				if (!copyFileTree(contentDir, contentFolder, masks[i])) {
					showError("�� ������� ����������� ����� � ������ \"" + masks[i] +
						"\" �� \"" + contentDir + "\" � \"" + contentFolder + "\"");
					return false;
				}
			}
		}
		return true;
	}
}