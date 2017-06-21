#include "pch.h"
#include "ThreadApi.h"
#include "ThreadEmulation.h"

namespace QuestNavigator {
	ThreadApi::ThreadApi()
	{
	}

	ThreadApi::~ThreadApi()
	{
	}

	HANDLE ThreadApi::createThread(
		LPSECURITY_ATTRIBUTES unusedThreadAttributes, 
		SIZE_T unusedStackSize, 
		LPTHREAD_START_ROUTINE lpStartAddress, 
		LPVOID lpParameter, 
		DWORD dwCreationFlags, 
		LPDWORD unusedThreadId
	)
	{
		return ThreadEmulation::CreateThread(
			unusedThreadAttributes,
			unusedStackSize,
			lpStartAddress,
			lpParameter,
			dwCreationFlags,
			unusedThreadId
		);
	}
}