#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		// JsListener
		void executeAction(int pos);
		void selectObject(int pos);
		void loadSlotSelected(int index);
		void saveSlotSelected(int index);
		void msgClosed();
		void errorClosed();
		void menuClosed(int pos);
		void inputClosed(string text);
		void mute(bool flag);
		void inputStringChanged(string text);
		void inputStringEntered();

		// App
		void runGame(string fileName, int gameIsStandalone);
		void stopGame();

		// ������ � �������� � ��������������.
		
		// �������, ���� ����� ���������� �� ����� ����� � ��������� ���������.
		void waitForLibIsReady();

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
