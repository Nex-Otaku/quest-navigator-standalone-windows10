#pragma once

namespace QuestNavigator
{
	class Library
	{
	public:
		Library();
		~Library();

		// ������ ������ ����������
		void StartLibThread();
		// ��������� ������ ����������
		void StopLibThread();
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