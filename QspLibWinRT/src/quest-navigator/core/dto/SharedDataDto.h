#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	struct SharedDataDto
	{
		string str;
		int num;
		//JSValue jsValue; Данные для передачи вызова из библиотеки (из кода игры) в яваскрипт.
		bool flag;
	};
}