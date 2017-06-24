#include "thread_sync.h"
#include "..\..\core\dialogs.h"

namespace QuestNavigator {
	//// Ожидаем события
	//bool waitForSingle(HANDLE handle)
	//{
	//	//DWORD res = WaitForSingleObject(handle, INFINITE);
	//	DWORD res = WaitForSingleObjectEx(handle, INFINITE, FALSE);
	//	if (res != WAIT_OBJECT_0) {
	//		showError("waitForSingle: Не удалось дождаться события синхронизации");
	//		return false;
	//	}
	//	return true;
	//}

	//// Высвобождаем описатель и ругаемся если что не так.
	//void freeHandle(HANDLE handle)
	//{
	//	BOOL res = CloseHandle(handle);
	//	if (res == 0) {
	//		showError("Не удалось высвободить описатель объекта ядра.");

	//		// STUB
	//		// Выход из приложения?
	//		//exit(eecFailToCloseHandle);
	//	}
	//}
}