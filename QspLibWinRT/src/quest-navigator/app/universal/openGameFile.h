#pragma once

#include <string>
#include <Windows.h>

using namespace std;

namespace QuestNavigator {
	// ƒиалог дл¤ открыти¤ файла игры с диска.
	string openGameFileDialog(HWND hWnd);
}