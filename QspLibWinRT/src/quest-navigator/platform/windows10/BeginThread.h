#pragma once

#include "pch.h"

namespace QuestNavigator {
	_Use_decl_annotations_ HANDLE WINAPI UwpCustomBeginThread(LPSECURITY_ATTRIBUTES unusedThreadAttributes, SIZE_T unusedStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD unusedThreadId);
}