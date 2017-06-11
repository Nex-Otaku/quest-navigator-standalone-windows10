#include "pch.h"
#include "Hello.h"

using namespace QspLibWinRT;
using namespace Platform;

Hello::Hello()
{
}

Platform::String^ Hello::GetMessage()
{
	return "Привет, мир!";
}


Platform::String^ Hello::GetModifiedMessage(Platform::String^ message)
{
	return "Вы прислали строку: " + message;
}