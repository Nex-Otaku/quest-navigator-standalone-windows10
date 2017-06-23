#include "pch.h"
#include "StringConverter.h"

using namespace std;

// Конвертация строк взята из ответа на StackOverflow, см. принятый ответ.
// https://stackoverflow.com/questions/28759212/convert-platformstring-to-stdstring

namespace QuestNavigator
{
	StringConverter::StringConverter()
	{
	}

	StringConverter::~StringConverter()
	{
	}

	Platform::String^ StringConverter::convertStdToUwp(string input)
	{
		auto utf8Data = input.c_str();
		int bufferSize = MultiByteToWideChar(CP_UTF8, 0, utf8Data, -1, nullptr, 0);
		auto wide = std::make_unique<wchar_t[]>(bufferSize);
		if (0 == MultiByteToWideChar(CP_UTF8, 0, utf8Data, -1, wide.get(), bufferSize)) {
			throw std::exception("Can't convert string to Unicode");
		}
		std::wstring w_str = std::wstring(wide.get());
		const wchar_t* w_chars = w_str.c_str();
		return (ref new Platform::String(w_chars));
	}

	string StringConverter::convertUwpToStd(Platform::String^ input)
	{
		std::wstring wide = input->Data();
		auto wideData = wide.c_str();
		int bufferSize = WideCharToMultiByte(CP_UTF8, 0, wideData, -1, nullptr, 0, NULL, NULL);
		auto utf8 = std::make_unique<char[]>(bufferSize);
		if (0 == WideCharToMultiByte(CP_UTF8, 0, wideData, -1, utf8.get(), bufferSize, NULL, NULL)) {
			throw std::exception("Can't convert string to UTF8");
		}
		return std::string(utf8.get());
	}
}