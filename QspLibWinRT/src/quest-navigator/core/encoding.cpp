#include "encoding.h"

namespace QuestNavigator {

	//// UTF-16 wstring -> UTF-16 WebString
	//WebString WideToWebString(wstring str)
	//{
	//	WebString cmd((wchar16*)str.data());
	//	return cmd;
	//}

	// UTF-16 wstring -> UTF-8 string
	string narrow(wstring str)
	{
		//WebString webStr = WideToWebString(str);
		//return ToString(webStr);
	}
	string fromQsp(QSP_CHAR* str)
	{
		wstring wStr = L"";
		if (str != NULL)
			wStr = str;
		return narrow(wStr);
	}
	string fromQsp(const QSP_CHAR* str)
	{
		return fromQsp((QSP_CHAR*)str);
	}

	// UTF-8 string -> UTF-16 wstring
	wstring widen(string str)
	{
		//WebString webStr = ToWebString(str);
		//wstring wStr = wstring((wchar_t*)webStr.data());
		//return wStr;
	}
}