#pragma once

#include "EventManager.h"
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"

namespace QuestNavigator
{
	class Library
	{
	public:
		Library();
		~Library();

		void Library::inject(
			EventManager* eventManager
		);

		// ������ ������ ����������
		void StartLibThread();
		// ��������� ������ ����������
		void StopLibThread();

	protected:
		// ��� ������ �� �������.
		EventManager* getEventManager();

	private:
		EventManager* eventManager;

		HANDLE libThread;

		// �������� ������� ������ ����������
		static unsigned int __stdcall libThreadFunc(void* pvParam);
		
		// �������� ����������� ���������� ������������� ����
		static void CheckQspResult(QSP_BOOL successfull, string failMsg);

		// ********************************************************************
		// ���������� ����������
		// ********************************************************************
		
		static string jsExecBuffer;
		static clock_t gameStartTime;
	};
	//		// ********************************************************************
	//		// THREADS
	//		// ********************************************************************
	//
	//		// ������ ������ ����������
	//		void StartLibThread();
	//		// ��������� ������ ����������
	//		void StopLibThread();
	//		// �������� ������� ������ ����������
	//		static unsigned int __stdcall libThreadFunc(void* pvParam);
	//
	//		// �������� ����������� ���������� ������������� ����
	//		static void CheckQspResult(QSP_BOOL successfull, string failMsg);

	//		// ********************************************************************
	//		// ���������� ����������
	//		// ********************************************************************
	//
	//		static string jsExecBuffer;
	//		static string lastMainDesc;
	//		static QnApplicationListener* listener;
	//		static vector<ContainerMenuItem> menuList;
	//		static clock_t gameStartTime;
	//		static int timerInterval;
	//
	//		static int objectSelectionIndex;
	//
}