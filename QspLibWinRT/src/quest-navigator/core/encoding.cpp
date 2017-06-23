#include "encoding.h"
#include <string>
#include <Windows.h>
#include <memory>

using namespace std;

namespace QuestNavigator {

	// UTF-16 wstring -> UTF-8 string
	string narrow(wstring str)
	{
		//std::wstring wide = input->Data();
		auto wideData = str.c_str();
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideData, -1, nullptr, 0, NULL, NULL);
		auto utf8 = std::make_unique<char[]>(bufferSize);
		if (0 == WideCharToMultiByte(CP_UTF8, 0, wideData, -1, utf8.get(), bufferSize, NULL, NULL)) {
			throw std::exception("Can't convert string to UTF8");
		}
		return std::string(utf8.get());
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
		auto utf8Data = str.c_str();
		int bufferSize = MultiByteToWideChar(CP_UTF8, 0, utf8Data, -1, nullptr, 0);
		auto wide = std::make_unique<wchar_t[]>(bufferSize);
		if (0 == MultiByteToWideChar(CP_UTF8, 0, utf8Data, -1, wide.get(), bufferSize)) {
			throw std::exception("Can't convert string to Unicode");
		}
		std::wstring w_str = std::wstring(wide.get());
		return w_str;
	}
}