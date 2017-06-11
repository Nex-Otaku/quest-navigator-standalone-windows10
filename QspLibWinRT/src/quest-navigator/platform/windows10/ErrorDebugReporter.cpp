#include "pch.h"
#include "ErrorDebugReporter.h"

namespace QuestNavigator
{
	ErrorDebugReporter* ErrorDebugReporter::instance()
	{
		static ErrorDebugReporter inst;
		return &inst;
	}

	void ErrorDebugReporter::inject(UwpJsExecutor ^ uwpJsExecutor)
	{
		this->uwpJsExecutor = uwpJsExecutor;
	}

	ErrorDebugReporter::ErrorDebugReporter()
	{
	}

	ErrorDebugReporter::~ErrorDebugReporter()
	{
	}

	void ErrorDebugReporter::showError(string message)
	{
		this->uwpJsExecutor->jsCallDebug(convertFromString("ERROR " + message));
	}

	Platform::String^ ErrorDebugReporter::convertFromString(string input)
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
}