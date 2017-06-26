#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "EventManager.h"
#include "Library.h"
#include "ConfigurationBuilder.h"

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
			Library* library,
			ConfigurationBuilder* configurationBuilder
		);

		void init();

		void runGame(string fileName);
		void StopGame(bool restart);
		void runNewGame(string contentPath);
		void executeCode(string qspCode);

	private:
		EventManager* eventManager;
		Library* library;
		ConfigurationBuilder* configurationBuilder;

		bool gameIsRunning;

		void initLib();
		void FreeResources();

		//		// ********************************************************************
		//		// ********************************************************************
		//		// ********************************************************************
		//		//                   Основная логика
		//		// ********************************************************************
		//		// ********************************************************************
		//		// ********************************************************************
		//
		//		// Устанавливаем мьютекс для управления экземплярами плеера.
		//		bool registerInstance();
		//		// Сбрасываем мьютекс для управления экземпл¤рами плеера.
		//		void unregisterInstance();
		//
		//		// Хэндл основного окна плеера.
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