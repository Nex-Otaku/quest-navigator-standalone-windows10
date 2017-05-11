#pragma once

namespace QuestNavigator
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		void executeAction(int pos);
		void selectObject(int pos);

		// ������ � �������� � ��������������.

	private:
		// ������ ������� ��� ������������� �������
		enum eSyncEvent
		{
			// Ui -> ����������
		
			evRunGame = 0,			// ��������� ����.
			evStopGame,				// ���������� ����.
			evShutdown,				// ��������� ������ ������.
			evExecuteCode,			// ��������� ������ ����.
			evExecuteAction,		// ��������� ��������.
			evSelectObject,			// ������� �������.
			evMute,					// �������� / ��������� ����.
		
			evJsExecuted,			// JS-������ ��������.
			evMsgClosed,			// ������ MSG ��� ������.
			evMenuClosed,			// ������ ����� ����������������� ����.
			evInputClosed,			// ������ INPUT ������ ���������.
			evErrorClosed,			// ������ � ���������� �� ������ ��� ������.
			evLoadSlotSelected,		// ��� ������ ���� ��� ��������.
			evSaveSlotSelected,		// ��� ������ ���� ��� ����������.
			evInputStringChanged,	// ��������� ����� � ������ �����.
			evInputStringEntered,	// ������ Enter � ������ �����.
		
			evTimer,				// �������� ������
		
			evLastUi,				// ������ ��� ���������� ������� �� ��� �����.
		
			// ���������� -> Ui
		
			evJsCommitted,			// ��������� JS-������.
		
			evGameStopped,			// ���� �����������.
		
			evLibIsReady,			// ���������� ��������� ���������� ���� 
			// � ������� ��������� �������.
		
			evLast
		};

		// ������ ������ ���� ��� ������������� �������,
		// ������� � �����������, ������������������ � ������� ���������.
		HANDLE CreateSyncEvent();
		// ������ ������.
		HANDLE CreateTimer();
		// �������� HANDLE ������� �� ��� �������
		HANDLE getEventHandle(eSyncEvent ev);
		// ��������� �������
		void runSyncEvent(eSyncEvent ev);
		// ������������ ��������� � �������� ���� ��� �� ���.
		void freeHandle(HANDLE handle);
		// ������ � ����������� ������
		void lockData();
		// ������� �� ����������� ������
		void unlockData();
		// ������� �������
		bool waitForSingle(HANDLE handle);
		bool waitForSingle(eSyncEvent ev);
		bool waitForSingleLib(eSyncEvent ev);
		bool checkForSingle(eSyncEvent ev);
	};
}
