#pragma once

#include "UwpJsExecutor.h"
#include <string>
#include "StringConverter.h"

using namespace QspLibWinRT;
using namespace std;

namespace QuestNavigator
{
	class ErrorDebugReporter
	{
	public:
		// Чтобы развязать статику, приходится обращаться через синглтон.
		static ErrorDebugReporter* instance();

		void inject(
			UwpJsExecutor^ uwpJsExecutor,
			StringConverter* stringConverter
		);

		void showError(string message);

	private:
		UwpJsExecutor^ uwpJsExecutor;
		StringConverter* stringConverter;

		// Убираем конструктор в приватную область,
		// так как мы используем синглтон, 
		// и создавать объект вне самого класса не будем.
		// Объект создаётся только в методе "instance".
		ErrorDebugReporter();
		~ErrorDebugReporter();
	};
}