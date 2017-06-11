#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "EventManager.h"
#include "Library.h"

using namespace std;

namespace QuestNavigator
{
	class App
	{
	public:
		App();
		~App();

		void inject(
			EventManager* eventManager,
			Library* library
		);

		void init();

		void runGame(string fileName);
		void StopGame(bool restart);
		void runNewGame(string contentPath);

		SaveSlotsDto getSaveSlots(bool open);

	private:
		EventManager* eventManager;
		Library* library;

		bool gameIsRunning;

		void initLib();
		void FreeResources();

		//		// ********************************************************************
		//		// ********************************************************************
		//		// ********************************************************************
		//		//                   ќсновна¤ логика
		//		// ********************************************************************
		//		// ********************************************************************
		//		// ********************************************************************
		//
		//		// ”станавливаем мьютекс дл¤ управлени¤ экземпл¤рами плеера.
		//		bool registerInstance();
		//		// —брасываем мьютекс дл¤ управлени¤ экземпл¤рами плеера.
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