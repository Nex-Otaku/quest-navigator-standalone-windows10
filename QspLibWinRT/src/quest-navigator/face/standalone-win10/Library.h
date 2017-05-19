#pragma once

#include "EventManager.h"
#include "..\..\..\deps\qsp\bindings\default\qsp_default.h"
#include "Timer.h"

namespace QuestNavigator
{
	class Library
	{
	public:
		Library();
		~Library();

		void Library::inject(
			EventManager* eventManager,
			Timer* timer
		);

		// ������ ������ ����������
		void StartLibThread();
		// ��������� ������ ����������
		void StopLibThread();

		// �������� ����������� ���������� ������������� ����
		static void CheckQspResult(QSP_BOOL successfull, string failMsg);

	private:
		EventManager* eventManager;
		Timer* timer;

		HANDLE libThread;

		// �������� ������� ������ ����������
		static unsigned int __stdcall libThreadFunc(void* pvParam);
		
		// ********************************************************************
		// ���������� ����������
		// ********************************************************************
		
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
	//		static QnApplicationListener* listener;
}