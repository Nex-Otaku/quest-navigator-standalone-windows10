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

	DWORD ThreadApi::waitForSingleObject(HANDLE hHandle, DWORD dwMilliseconds)
	{
		return WaitForSingleObjectEx(hHandle, dwMilliseconds, FALSE);
	}

	BOOL ThreadApi::closeHandle(HANDLE hObject)
	{
		return CloseHandle(hObject);
	}

	DWORD ThreadApi::waitForMultipleObjects(
		DWORD nCount, 
		const HANDLE* lpHandles,
		BOOL bWaitAll,
		DWORD dwMilliseconds
	)
	{
		return WaitForMultipleObjectsEx(nCount, lpHandles, bWaitAll, dwMilliseconds, FALSE);
	}

	HANDLE ThreadApi::createEvent(
		LPSECURITY_ATTRIBUTES lpEventAttributes, 
		BOOL bManualReset, 
		BOOL bInitialState, 
		LPCWSTR lpName
	)
	{
		return CreateEventEx(lpEventAttributes, lpName, NULL, SYNCHRONIZE | EVENT_MODIFY_STATE /*NULL*//*EVENT_ALL_ACCESS*//*SYNCHRONIZE | EVENT_MODIFY_STATE*/);
	}

	BOOL ThreadApi::setEvent(HANDLE hEvent)
	{
		return SetEvent(hEvent);
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