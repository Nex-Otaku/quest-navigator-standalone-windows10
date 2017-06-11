#pragma once

#include <string>
#include "../../deps/qsp/bindings/default/qsp_default.h"

using namespace std;

namespace QuestNavigator {

	// ”тилиты дл¤ преобразовани¤ строк

	// UTF-16 wstring -> UTF-16 WebString
	//WebString WideToWebString(wstring str);
	// UTF-16 wstring -> UTF-8 string
	string narrow(wstring str);
	string fromQsp(QSP_CHAR* str);
	string fromQsp(const QSP_CHAR* str);
	// UTF-8 string -> UTF-16 wstring
	wstring widen(string str);
}