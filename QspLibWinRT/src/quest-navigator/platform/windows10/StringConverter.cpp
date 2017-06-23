#include "pch.h"
#include "StringConverter.h"

using namespace std;

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
		// https://stackoverflow.com/questions/28759212/convert-platformstring-to-stdstring
		// accepted answer, also revert conversion

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

	string StringConverter::convertUwpToStd(Platform::String ^ input)
	{
		// STUB
		return string();
	}
}