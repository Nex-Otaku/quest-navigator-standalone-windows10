#pragma once

#include "EventManager.h"

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

		EventManager* getEventManager();

	private:
		EventManager* eventManager;

		HANDLE libThread;

		// �������� ������� ������ ����������
		static unsigned int __stdcall libThreadFunc(void* pvParam);
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
}