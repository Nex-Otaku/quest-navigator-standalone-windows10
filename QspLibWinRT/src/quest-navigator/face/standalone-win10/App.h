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
		//		//                   ќсновна€ логика
		//		// ********************************************************************
		//		// ********************************************************************
		//		// ********************************************************************
		//
		//		// ”станавливаем мьютекс дл€ управлени€ экземпл€рами плеера.
		//		bool registerInstance();
		//		// —брасываем мьютекс дл€ управлени€ экземпл€рами плеера.
		//		void unregisterInstance();
		//
		//		// ’эндл основного окна плеера.
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