#pragma once

#include <string>
#include "dto\SaveSlotsDto.h"

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
		void runNewGame(string contentPath);

		// STUB
		//		JSObject getSaveSlots(bool open);
		SaveSlotsDto getSaveSlots(bool open);


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