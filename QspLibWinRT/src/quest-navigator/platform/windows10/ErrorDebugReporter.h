#pragma once

#include "UwpJsExecutor.h"
#include <string>

using namespace QspLibWinRT;
using namespace std;

namespace QuestNavigator
{
	class ErrorDebugReporter
	{
	public:
		// ����� ��������� �������, ���������� ���������� ����� ��������.
		static ErrorDebugReporter* instance();

		void inject(
			UwpJsExecutor^ uwpJsExecutor
		);

		void showError(string message);

	private:
		UwpJsExecutor^ uwpJsExecutor;

		// ����������� �����
		Platform::String^ convertFromString(string input);

		// ������� ����������� � ��������� �������,
		// ��� ��� �� ���������� ��������, 
		// � ��������� ������ ��� ������ ������ �� �����.
		// ������ �������� ������ � ������ "instance".
		ErrorDebugReporter();
		~ErrorDebugReporter();
	};
}