#pragma once

namespace QuestNavigator
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

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
	};
}