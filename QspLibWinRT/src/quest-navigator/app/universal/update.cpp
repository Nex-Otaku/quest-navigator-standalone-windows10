#include "update.h"

#ifdef _WIN32
//#include <winsparkle.h>
#endif

namespace QuestNavigator {

	// ��������� ������� ������� ��� ������
	void checkUpdate()
	{
		//// Initialize WinSparkle as soon as the app itself is initialized, right
		//// before entering the event loop:
		//win_sparkle_set_appcast_url(QN_WINDOWS_UPDATE_FEED.c_str());
		//win_sparkle_set_app_details(widen(QN_COMPANY_NAME).c_str(), 
		//	widen(QN_APP_NAME).c_str(),
		//	widen(QN_VERSION).c_str());

		//win_sparkle_init();
	}

	// ��������� ������ ��������� �� ������ �� ����������
	void finishUpdate()
	{
		//win_sparkle_cleanup();
	}
}