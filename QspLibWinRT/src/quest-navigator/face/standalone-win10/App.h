#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	class App
	{
	public:
		App();
		~App();

		void runGame(string fileName);
		void StopGame(bool restart);

		//		// ********************************************************************
		//		// ********************************************************************
		//		// ********************************************************************
		//		//                   �������� ������
		//		// ********************************************************************
		//		// ********************************************************************
		//		// ********************************************************************
		//
		//		// ������������� ������� ��� ���������� ������������ ������.
		//		bool registerInstance();
		//		// ���������� ������� ��� ���������� ������������ ������.
		//		void unregisterInstance();
		//
		//		// ����� ��������� ���� ������.
		//		HWND hwnd();
		//
		//		void initLib();
		//		void FreeResources();
		//		void runGame(string fileName);
		//		void StopGame(bool restart);
		//		void runNewGame(string contentPath);
		//		bool isGameRunning();
		//		JSObject getSaveSlots(bool open);
		//		virtual void executeCode(string qspCode);
		//		virtual bool textInputIsFocused();
		//		virtual void toggleFullscreen();
		//		virtual bool processIpcData(COPYDATASTRUCT* pCds);
	};
}