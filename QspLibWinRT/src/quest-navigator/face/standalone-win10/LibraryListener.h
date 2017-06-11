#pragma once

#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "JsExecutor.h"
#include "Timer.h"
#include "EventManager.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "Library.h"

namespace QuestNavigator
{
	class LibraryListener
	{
	public:
		// К библиотеке подвязаны статические колбэки, 
		// поэтому нам приходится использовать синглтон для доступа
		// к объекту LibraryListener и через него ко всем другим объектам.
		static LibraryListener* instance();

		void inject(
			JsExecutor* jsExecutor,
			Timer* timer,
			EventManager* eventManager,
			Library* library
		);

		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		//                       Колбэки интерпретатора
		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		
		static void RefreshInt(int isRedraw);
		static void SetTimer(int msecs);
		static void SetInputStrText(QSP_CHAR* text);
		static void ShowMessage(QSP_CHAR* message);
		static void PlayFile(QSP_CHAR* file, int volume);
		static QSP_BOOL IsPlayingFile(QSP_CHAR* file);
		static void CloseFile(QSP_CHAR* file);
		static void ShowPicture(QSP_CHAR* file);
		static void InputBox(const QSP_CHAR* prompt, QSP_CHAR* buffer, int maxLen);
		static void PlayerInfo(QSP_CHAR* resource, QSP_CHAR* buffer, int maxLen);
		static int GetMSCount();
		static void AddMenuItem(QSP_CHAR* name, QSP_CHAR* imgPath);
		static int ShowMenu();
		static void DeleteMenu();
		static void Wait(int msecs);
		static void ShowWindow(int type, QSP_BOOL isShow);
		static void System(QSP_CHAR* cmd);
		static void OpenGameStatus(QSP_CHAR* file);
		static void SaveGameStatus(QSP_CHAR* file);

		// Вспомогательная функция для очистки буфера.
		// В качестве колбека не используется.
		// TODO проверить, можно ли будет от неё избавиться, 
		// уж очень некрасиво получилось.
		static void resetJsExecBuffer();
		// Сбрасываем счётчик миллисекунд.
		static void resetMsCount();
		// Устанавливаем номер выделенного предмета.
		// TODO исправить в библиотеке, чтобы эта переменная не требовалась.
		// См. обработку evSelectObject в Library.
		static void setObjectSelectionIndex(int index);
	private:
		static string jsExecBuffer;
		static string lastMainDesc;
		static int objectSelectionIndex;
		static clock_t gameStartTime;
		static vector<MenuItemDto> menuList;

		// Убираем конструктор в приватную область,
		// так как мы используем синглтон, 
		// и создавать объект вне самого класса не будем.
		// Объект создаётся только в методе "instance".
		LibraryListener();
		~LibraryListener();

		JsExecutor* jsExecutor;
		Timer* timer;
		EventManager* eventManager;
		Library* library;
	};
}