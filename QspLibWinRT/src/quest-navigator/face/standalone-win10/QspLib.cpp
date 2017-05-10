#include "pch.h"
#include "QspLib.h"

using namespace QuestNavigator;

namespace QspLibWinRT
{

	QspLib::QspLib()
	{
		// Этот файл является корневым для приложения.
		// Так называемая "точка сборки".
		// Именно здесь мы указываем, какие реализации интерфейсов следует применять,
		// и соответственно создаём все конкретные объекты, привязываем зависимости.

		// Создаём объект, который будет "слушать" вызовы яваскриптового API.
		this->jsListener = new JsListener();
	}

	// Колбэки из яваскрипта к функциям API плеера.

	// По приведению типов int, bool, wchar_t
	// см. таблицу
	// https://docs.microsoft.com/en-us/cpp/cppcx/fundamental-types-c-cx
	// По строкам и массивам см.
	// https://docs.microsoft.com/en-us/cpp/cppcx/type-system-c-cx

	void QspLib::restartGame()
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::executeAction(int32 pos)
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::selectObject(int32 pos)
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::loadGame()
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::saveGame()
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::saveSlotSelected(int32 index, int32 mode)
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::msgResult()
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::errorResult()
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::userMenuResult(int32 pos)
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::inputResult(Platform::String ^ text)
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::setMute(Platform::Boolean flag)
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::setInputString(Platform::String ^ text)
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::runInputString()
	{
		throw ref new Platform::NotImplementedException();
	}

	void QspLib::runDefaultGame()
	{
		throw ref new Platform::NotImplementedException();
	}
}