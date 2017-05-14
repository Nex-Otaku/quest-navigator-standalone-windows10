#pragma once

#include <Windows.h>

namespace QuestNavigator {

	// Вспомогательные функции для синхронизации потоков.

	// Ожидаем события
	bool waitForSingle(HANDLE handle);
	// Высвобождаем описатель и ругаемся если что не так.
	void freeHandle(HANDLE handle);
}