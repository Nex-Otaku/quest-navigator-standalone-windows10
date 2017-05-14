#pragma once

#include <string>
#include "Timer.h"
#include "..\..\core\events.h"
#include "..\..\core\dto\SharedDataDto.h"

using namespace std;

namespace QuestNavigator
{
	class EventManager
	{
	public:
		EventManager();
		~EventManager();

		void inject(
			Timer* timer
		);

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

		// Library
		void initEvents();
		void initSharedData();
		void freeEvents();
		void freeSharedData();

		void shutdown();
		void libIsReady();

		DWORD waitForAnyEvent();
		bool isValidEvent(DWORD waitResult);
		SharedDataDto getSharedData(eSyncEvent ev);

		// ������ � �������� � ��������������.
		
		// �������, ���� ����� ���������� �� ����� ����� � ��������� ���������.
		void waitForLibIsReady();

	private:
		Timer* timer;

		// ���������� ��� ������ � ��������

		// ��������� ��� ����������� ������
		CRITICAL_SECTION g_csSharedData;

		// ����������� ������
		SharedDataDto g_sharedData[evLast];

		// ������� ��� ������������� �������
		HANDLE g_eventList[evLast];

		// ������ ������ ���� ��� ������������� �������,
		// ������� � �����������, ������������������ � ������� ���������.
		HANDLE CreateSyncEvent();
		// �������� HANDLE ������� �� ��� �������
		HANDLE getEventHandle(eSyncEvent ev);
		// ��������� �������
		void runSyncEvent(eSyncEvent ev);
		// ������ � ����������� ������
		void lockData();
		// ������� �� ����������� ������
		void unlockData();
		// ������� �������
		bool waitForSingleEvent(eSyncEvent ev);
		bool waitForSingleLib(eSyncEvent ev);
		bool checkForSingleEvent(eSyncEvent ev);
	};
}
