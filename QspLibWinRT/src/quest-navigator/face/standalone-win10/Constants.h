#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {
	static const string DEFAULT_CONTENT_REL_PATH = "standalone_content";
	static const string ASSETS_DIR = "assets";
	static const string SKINS_DIR = "skins";
	static const string QSPLIB_DIR = "qsplib";
	static const string APP_DATA_DIR = "Quest Navigator Data";
	static const string GAME_CACHE_DIR = "Cached Games";
	static const string DEFAULT_SKIN_NAME = "default";
	static const string DEFAULT_SKIN_FILE = "gameAwesomium.html";
	static const string DEFAULT_CONFIG_FILE = "config.xml";
	static const string DEFAULT_SAVE_REL_PATH = "Сохранения игр Quest Navigator";
	static const string QN_WINDOWS_UPDATE_FEED = "http://feeds.feedburner.com/text-games/quest-navigator-windows";
	static const string QN_COMPANY_NAME = "QSP";
	static const string QN_APP_NAME = "Quest Navigator";
	static const string QN_VERSION = "0.0.29-test";
	static const string QN_APP_GUID = "95b90169-f70d-4269-b982-d9c3038b8348";
	static const wchar_t szWindowClass[] = L"QnViewWinClass";
	static const wchar_t szLogWindowClass[] = L"QnLogWinClass";

	static const string OPTION_ENABLE_SOUND_CACHE = "-enable-sound-cache";
	static const string OPTION_DEFAULT_SKIN = "-default-skin";
	static const string OPTION_RESTART = "-restart";
	static const string PATH_DELIMITER = "\\";
}