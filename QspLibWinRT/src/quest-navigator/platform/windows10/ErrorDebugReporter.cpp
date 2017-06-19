#include "pch.h"
#include "ErrorDebugReporter.h"

namespace QuestNavigator
{
	ErrorDebugReporter* ErrorDebugReporter::instance()
	{
		static ErrorDebugReporter inst;
		return &inst;
	}

	void ErrorDebugReporter::inject(UwpJsExecutor^ uwpJsExecutor, StringConverter* stringConverter)
	{
		this->uwpJsExecutor = uwpJsExecutor;
		this->stringConverter = stringConverter;
	}

	ErrorDebugReporter::ErrorDebugReporter()
	{
	}

	ErrorDebugReporter::~ErrorDebugReporter()
	{
	}

	void ErrorDebugReporter::showError(string message)
	{
		Platform::String^ pMessage = stringConverter->convertFromString("ERROR " + message);
		this->uwpJsExecutor->jsCallDebug(pMessage);
	}
}