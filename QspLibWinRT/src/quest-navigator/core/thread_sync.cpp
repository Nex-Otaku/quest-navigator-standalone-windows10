#include "thread_sync.h"
#include "dialogs.h"

namespace QuestNavigator {
	// Ожидаем события
	bool waitForSingle(HANDLE handle)
	{
		DWORD res = WaitForSingleObject(handle, INFINITE);
		if (res != WAIT_OBJECT_0) {
			showError("Не удалось дождаться события синхронизации");
			return false;
		}
		return true;
	}

	// Высвобождаем описатель и ругаемся если что не так.
	void freeHandle(HANDLE handle)
	{
		BOOL res = CloseHandle(handle);
		if (res == 0) {
			showError("Не удалось высвободить описатель объекта ядра.");

			// STUB
			// Выход из приложения?
			//exit(eecFailToCloseHandle);
		}
	}
}