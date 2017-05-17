#pragma once

#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "JsExecutor.h"
#include "Timer.h"

namespace QuestNavigator
{
	class LibraryListener
	{
	public:
		// � ���������� ��������� ����������� �������, 
		// ������� ��� ���������� ������������ �������� ��� �������
		// � ������� LibraryListener � ����� ���� �� ���� ������ ��������.
		static LibraryListener* instance();

		void inject(
			JsExecutor* jsExecutor,
			Timer* timer
		);

		// ********************************************************************
		// ********************************************************************
		// ********************************************************************
		//                       ������� ��������������
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

		// ��������������� ������� ��� ������� ������.
		// � �������� ������� �� ������������.
		// TODO ���������, ����� �� ����� �� �� ����������, 
		// �� ����� ��������� ����������.
		static void resetJsExecBuffer();
		// ���������� ������� �����������.
		static void resetMsCount();
	private:
		static string jsExecBuffer;
		static string lastMainDesc;
		static int objectSelectionIndex;
		static clock_t gameStartTime;

		// ������� ����������� � ��������� �������,
		// ��� ��� �� ���������� ��������, 
		// � ��������� ������ ��� ������ ������ �� �����.
		// ������ �������� ������ � ������ "instance".
		LibraryListener();
		~LibraryListener();

		JsExecutor* jsExecutor;
		Timer* timer;
	};
	//		// ********************************************************************
	//		// ********************************************************************
	//		// ********************************************************************
	//		//                       ������� ��������������
	//		// ********************************************************************
	//		// ********************************************************************
	//		// ********************************************************************
	//
	//		static void RefreshInt(int isRedraw);
	//		static void SetTimer(int msecs);
	//		static void SetInputStrText(QSP_CHAR* text);
	//		static void ShowMessage(QSP_CHAR* message);
	//		static void PlayFile(QSP_CHAR* file, int volume);
	//		static QSP_BOOL IsPlayingFile(QSP_CHAR* file);
	//		static void CloseFile(QSP_CHAR* file);
	//		static void ShowPicture(QSP_CHAR* file);
	//		static void InputBox(const QSP_CHAR* prompt, QSP_CHAR* buffer, int maxLen);
	//		static void PlayerInfo(QSP_CHAR* resource, QSP_CHAR* buffer, int maxLen);
	//		static int GetMSCount();
	//		static void AddMenuItem(QSP_CHAR* name, QSP_CHAR* imgPath);
	//		static int ShowMenu();
	//		static void DeleteMenu();
	//		static void Wait(int msecs);
	//		static void ShowWindow(int type, QSP_BOOL isShow);
	//		static void System(QSP_CHAR* cmd);
	//		static void OpenGameStatus(QSP_CHAR* file);
	//		static void SaveGameStatus(QSP_CHAR* file);
}