#include "pch.h"
#include "ConfigurationBuilder.h"

namespace QuestNavigator
{
	ConfigurationBuilder::ConfigurationBuilder()
	{
	}

	ConfigurationBuilder::~ConfigurationBuilder()
	{
	}

	bool ConfigurationBuilder::build()
	{
		//// ������������� ��������� �� ���������
		//Configuration::setBool(ecpSoundCacheEnabled, false);
		//Configuration::setInt(ecpSaveSlotMax, 5);
		//Configuration::setString(ecpDefaultSkinName, DEFAULT_SKIN_NAME);
		//Configuration::setBool(ecpLimitSingleInstance, false);
		//Configuration::setString(ecpCacheDir, "");

		//// ��������� ��������� �������
		//int argCount = 0;
		//LPWSTR* szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
		//if (szArgList == NULL) {
		//	showError("�� ���� �������� ��������� ��������� ������");
		//	return false;
		//}
		//vector<string> params;
		//for (int i = 0; i < argCount; i++) {
		//	params.push_back(trim(narrow(szArgList[i])));
		//}
		//LocalFree(szArgList);
		//bool contentPathSet = contentPath != "";
		//bool contentPathFound = false;
		//for (int i = 0; i < argCount; i++) {
		//	string param = params[i];
		//	// ���� �� �������� ��������� �� ��������� ������,
		//	// �� ������ ���������� ��� ��� exe-�����, ���������� ���.
		//	if (endsWith(param, ".exe"))
		//		continue;
		//	bool isOption = startsWith(param, "-");
		//	// ��� �������� ���� � ����� ���� � ��������� ������.
		//	// ������ ��������� ���, ��������� ����� �����,
		//	// ����� �������� ��� ������ ���������� ��������� ���������.
		//	if (!contentPathFound && !isOption) {
		//		// ���� ��� ������� �������� ���� � ����� ����, 
		//		// �� �� ���������� ����, ��������� � ��������� ������.
		//		// �������� �������� - ����� ������������ ���� � "����� ���".
		//		// ��� ������� ������ ������� ���� ����, � ��� ������ ����� ������.
		//		if (!contentPathSet) {
		//			contentPath = param;
		//			contentPathSet = true;
		//		}
		//		contentPathFound = true;
		//	} else if (isOption) {
		//		// ��������� �����
		//		if (param == OPTION_ENABLE_SOUND_CACHE) {
		//			// ���������� �� �������� �����.
		//			Configuration::setBool(ecpSoundCacheEnabled, true);
		//		} else if (startsWith(param, OPTION_DEFAULT_SKIN)) {
		//			// ����� �� ����������� �������� �������� �� ��������� ��� ����, 
		//			// ��� ���������� � ���� ������ �������, 
		//			// � ���������� �������� � ������� ����.
		//			if (i + 1 == argCount) {
		//				showError("�� ������� ��� ������� ��� ����� " + OPTION_DEFAULT_SKIN);
		//			}
		//			Configuration::setString(ecpDefaultSkinName, params[i + 1]);
		//			i++;
		//		} else if (param == OPTION_RESTART) {
		//			// ����� "������" ���� ������.
		//			// ������������ ��� �������������� ����, 
		//			// ����� ��������� ���������� ������ 
		//			// ��� �������� ������ � ���������� ������� �������.
		//			Configuration::setBool(ecpLimitSingleInstance, true);
		//		} else {
		//			showError("����������� �����: [" + param + "]");
		//			return false;
		//		}
		//	} else {
		//		showError("����������� ��������: [" + param + "]\n" +
		//			"��������, ���� � ����� �������� ������� � �� ������ ����� ��� � �������.");
		//		return false;
		//	}
		//}
		//// �� ��������� ���������.

		//// ���������� ���� ��� �������.
		//// 1. ���� ���� ������� ���������� ��������� ������, ��������� �.
		//// 2. ���� �������� �� ������, ���� ���� � ����� ������.
		//// 3. ���� � ����� ������ ���� �� �������, ���� ����������� �� assets\standalone_content

		//string contentDir = "";
		//string skinFilePath = "";
		//string gameFileName = "";
		//string gameFilePath = "";
		//string configFilePath = "";
		//string saveDir = "";
		//string windowTitle = QN_APP_NAME + " " + QN_VERSION;
		//bool runningDefaultGame = false;
		//if (contentPathSet) {
		//	// ��� �������� ���� � ����.
		//	// ����� ��� ��������:
		//	// 1. ��� ���� � ������ .qn;
		//	// 2. ��� ���� � ����� .qsp;
		//	// 3. ��� ���� � ����� ����.
		//	// ��������� ���� �� ������������� � ����������.

		//	bool bValidDirectory = dirExists(contentPath);
		//	bool bValidFile = !bValidDirectory && fileExists(contentPath);
		//	// ���� � ����� ���� ������ ���� ����������.
		//	// ���� �� ����� �������������,
		//	// ���������� �� ������ ��������� ��������� QSP-������.
		//	if (bValidFile || bValidDirectory) {
		//		contentPath = relativePathToAbsolute(contentPath);
		//	}
		//	if (bValidFile) {
		//		// ��������� ���������� �����
		//		bool bExtQn = endsWith(contentPath, ".qn");
		//		bool bExtQsp = endsWith(contentPath, ".qsp");
		//		if (!bExtQn && !bExtQsp) {
		//			showError("����������� ������ �����!\n�������������� �������: qn, qsp");
		//			return false;
		//		}
		//		if (bExtQn) {
		//			// STUB
		//			showError("�������� ������ qn ��� �� �����������.");
		//			return false;
		//		} else {
		//			// ��������� ���� � ����� ����
		//			gameFilePath = contentPath;
		//			gameFileName = contentPath;
		//			// ��������� ���� � ����� ����
		//			if (contentPath.length() > 0) {
		//				int pos = contentPath.find_last_of(PATH_DELIMITER);
		//				if  (pos != string::npos) {
		//					contentDir = contentPath.substr(0, pos);
		//					gameFileName = contentPath.substr(pos + 1);
		//				}
		//			}
		//			// ��������� ���� � ����������� ������
		//			skinFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_SKIN_FILE);
		//			configFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_CONFIG_FILE);
		//		}
		//		// STUB
		//	} else if (bValidDirectory) {
		//		// ��������� ���� � ����� ����.
		//		// ���� � ��������� ����� ���� ��������� ����� "standalone_content",
		//		// �� ������� � ������ ����. ����� ������� ������ ���� ��������� �����.
		//		string deepDir = contentPath + PATH_DELIMITER + DEFAULT_CONTENT_REL_PATH;
		//		if (dirExists(deepDir)) {
		//			contentDir = deepDir;
		//		} else {
		//			contentDir = contentPath;
		//		}

		//		// ��������� ���� � ����������� ������
		//		skinFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_SKIN_FILE);
		//		// ���������� ���� ���� (*.qsp) � ��������� �����.
		//		if (!findGameFile(contentDir, gameFileName))
		//			return false;
		//		gameFilePath = getRightPath(contentDir + PATH_DELIMITER + gameFileName);
		//		configFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_CONFIG_FILE);
		//	} else {
		//		DWORD error = GetLastError();
		//		if (error == ERROR_FILE_NOT_FOUND) {
		//			showError("�� ������ ����: [" + contentPath + "]");
		//		} else if (error == ERROR_PATH_NOT_FOUND) {
		//			showError("�� ������ ����: [" + contentPath + "]");
		//		} else {
		//			showError("�� ������� �������� ����: [" + contentPath + "]");
		//		}
		//		return false;
		//	}
		//}
		//
		//if (contentDir == "") {
		//	// ��������� ���� �� ���������
		//	runningDefaultGame = true;
		//	string assetsDir = getPlayerDir() + PATH_DELIMITER + ASSETS_DIR;
		//	configFilePath = getRightPath(assetsDir + PATH_DELIMITER 
		//		+ DEFAULT_CONTENT_REL_PATH + PATH_DELIMITER 
		//		+ DEFAULT_CONFIG_FILE);
		//	contentDir = assetsDir + PATH_DELIMITER + DEFAULT_CONTENT_REL_PATH;
		//	// ���������� ���� ���� (*.qsp) � ��������� �����.
		//	if (!findGameFile(contentDir, gameFileName))
		//		return false;
		//	gameFilePath = contentDir + PATH_DELIMITER + gameFileName;
		//	skinFilePath = getRightPath(contentDir + PATH_DELIMITER + DEFAULT_SKIN_FILE);
		//}

		//// �������� ���� � ����� ���� � ���������� �����.
		//gameFilePath = canonicalizePath(gameFilePath);
		//
		//// ������� ���������� ��� ����.
		//string gameHash = md5(gameFilePath);

		//// ����� ��� ����������
		//saveDir = "";
		//// ���� � ���������������� ����� "��� ���������"
		//WCHAR wszPath[MAX_PATH];
		//HRESULT hr = SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, SHGFP_TYPE_CURRENT, wszPath);
		//if (hr != S_OK) {
		//	showError("�� ������� �������� ���� � ����� \"��� ���������\".");
		//	return false;
		//}
		//saveDir = getRightPath(narrow(wszPath) + PATH_DELIMITER + DEFAULT_SAVE_REL_PATH + PATH_DELIMITER + gameHash);

		//// ����� � ������� ����������.
		//// � ��� ��������� ��, � ����� ������������ ����.
		//hr = SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, wszPath);
		//if (hr != S_OK) {
		//	showError("�� ������� �������� ���� � ����� \"Application Data\".");
		//	return false;
		//}
		//string appDataDir = narrow(wszPath) + PATH_DELIMITER + APP_DATA_DIR;

		//// �������� ��� ���� � ���������� �����.
		//contentDir = canonicalizePath(contentDir);
		//skinFilePath = canonicalizePath(skinFilePath);
		//configFilePath = canonicalizePath(configFilePath);
		//saveDir = canonicalizePath(saveDir);
		//appDataDir = canonicalizePath(appDataDir);

		//// ��������� ��� ����� �� ����������
		//if (!fileExists(skinFilePath))
		//	skinFilePath = "";
		//if (!fileExists(configFilePath))
		//	configFilePath = "";
		//if (!fileExists(gameFilePath)) {
		//	showError("�� ������� ��������� ���� �� �����: " + gameFilePath);
		//	return false;
		//}

		//// ��������� ������������
		//Configuration::setString(ecpContentDir, contentDir);
		//Configuration::setString(ecpSkinFilePath, skinFilePath);
		//Configuration::setString(ecpGameFilePath, gameFilePath);
		//Configuration::setString(ecpGameHash, gameHash);
		//Configuration::setString(ecpGameFileName, gameFileName);
		//Configuration::setString(ecpConfigFilePath, configFilePath);
		//Configuration::setString(ecpSaveDir, saveDir);
		//Configuration::setString(ecpAppDataDir, appDataDir);
		//Configuration::setString(ecpWindowTitle, windowTitle);
		//Configuration::setBool(ecpIsFullscreen, false);
		//Configuration::setBool(ecpRunningDefaultGame, runningDefaultGame);

		//// ��������� ��������� ���� �� ����� config.xml
		//bool gameConfigLoaded = loadGameConfig();
		//if (!gameConfigLoaded)
		//	return false;

		//return true;
		return false;
	}
}