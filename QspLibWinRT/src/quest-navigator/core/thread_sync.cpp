#include "thread_sync.h"
#include "dialogs.h"

namespace QuestNavigator {
	// ������� �������
	bool waitForSingle(HANDLE handle)
	{
		DWORD res = WaitForSingleObject(handle, INFINITE);
		if (res != WAIT_OBJECT_0) {
			showError("�� ������� ��������� ������� �������������");
			return false;
		}
		return true;
	}

	// ������������ ��������� � �������� ���� ��� �� ���.
	void freeHandle(HANDLE handle)
	{
		BOOL res = CloseHandle(handle);
		if (res == 0) {
			showError("�� ������� ����������� ��������� ������� ����.");

			// STUB
			// ����� �� ����������?
			//exit(eecFailToCloseHandle);
		}
	}
}