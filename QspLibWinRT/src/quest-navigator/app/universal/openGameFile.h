#pragma once

#include <string>
#include <Windows.h>

using namespace std;

namespace QuestNavigator {
	// Диалог для открытия файла игры с диска.
	string openGameFileDialog(HWND hWnd);
}