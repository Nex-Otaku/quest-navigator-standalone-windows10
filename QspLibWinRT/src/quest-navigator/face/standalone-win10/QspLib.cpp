#include "pch.h"
#include "QspLib.h"
#include "EventManager.h"
#include "Timer.h"
#include "App.h"
#include "JsExecutor.h"
#include "Library.h"
#include "LibraryListener.h"
#include "..\..\platform\windows10\UwpJsExecutor.h"
#include "..\..\platform\windows10\ErrorDebugReporter.h"

using namespace QuestNavigator;
using namespace QspLibWinRT;

namespace QspLibWinRT
{

	QspLib::QspLib()
	{
		// ���� ���� �������� �������� ��� ����������.
		// ��� ���������� "����� ������".
		// ������ ����� �� ���������, ����� ���������� ����������� ������� ���������,
		// � �������������� ������ ��� ���������� �������, ����������� �����������.

		// ������ ������, ������� ����� "�������" ������ �������������� API.
		this->jsListener = new JsListener();
		// ������ ���������� �������.
		// ������� ������������ ��� ������������� � �������� ������ ����� ��������.
		EventManager* eventManager = new EventManager();
		// ������ ������ ��� ���������� ��������.
		Timer* timer = new Timer();
		// ������ ������ ����������.
		App* app = new App();
		// ������ ������ ��� ���������� ����������.
		JsExecutor* jsExecutor = new JsExecutor();
		// ������ ��������������� ������ ��� ���������� ����������, 
		// ������� �������� ��������������� �� ������ ���������.
		UwpJsExecutor^ uwpJsExecutor = ref new UwpJsExecutor();
		// ������ ������ ��� ���������� ������� ����������.
		Library* library = new Library();
		// ������ ��������-������ ��� ��������� �������� ����������.
		LibraryListener* libraryListener = LibraryListener::instance();
		// ������ ������ ��� ������ ������ - � ����� �������.
		ErrorDebugReporter* errorDebugReporter = ErrorDebugReporter::instance();

		// ������ �������� ������������.
		this->jsListener->inject(
			eventManager,
			app,
			timer,
			jsExecutor
		);
		app->inject(
			eventManager,
			library
		);
		library->inject(
			eventManager,
			timer,
			jsExecutor
		);
		eventManager->inject(timer, uwpJsExecutor);
		libraryListener->inject(
			jsExecutor,
			timer,
			eventManager,
			library
		);
		jsExecutor->inject(uwpJsExecutor);
		errorDebugReporter->inject(uwpJsExecutor);

		// ��������� ��������� �������� 
		// ��� ����������� �������� �������� � ����������
		// ����� ������ UwpJsExecutor.
		this->uwpJsExecutor = uwpJsExecutor;

		// ��������� ����������.
		app->init();
	}

	UwpJsExecutor^ QspLib::getUwpJsExecutor()
	{
		return this->uwpJsExecutor;
	}

	void QspLib::callDebugMessage()
	{
		this->uwpJsExecutor->jsCallDebug("simple debug call");
	}

	// ������� �� ���������� � �������� API ������.

	// �� ���������� ����� int, bool, wchar_t
	// ��. �������
	// https://docs.microsoft.com/en-us/cpp/cppcx/fundamental-types-c-cx
	// �� ������� � �������� ��.
	// https://docs.microsoft.com/en-us/cpp/cppcx/type-system-c-cx

	void QspLib::restartGame()
	{
		this->uwpJsExecutor->jsCallDebug("QspLib::restartGame() start");
		this->jsListener->restartGame();
		this->uwpJsExecutor->jsCallDebug("QspLib::restartGame() finish");
	}

	void QspLib::executeAction(int32 pos)
	{
		this->jsListener->executeAction((int)pos);
	}

	void QspLib::selectObject(int32 pos)
	{
		this->jsListener->selectObject((int)pos);
	}

	void QspLib::loadGame()
	{
		this->jsListener->loadGame();
	}

	void QspLib::saveGame()
	{
		this->jsListener->saveGame();
	}

	void QspLib::saveSlotSelected(int32 index, int32 mode)
	{
		this->jsListener->saveSlotSelected((int)index, (int)mode);
	}

	void QspLib::msgResult()
	{
		this->jsListener->msgResult();
	}

	void QspLib::errorResult()
	{
		this->jsListener->errorResult();
	}

	void QspLib::userMenuResult(int32 pos)
	{
		this->jsListener->userMenuResult((int)pos);
	}

	void QspLib::inputResult(Platform::String ^ text)
	{
		throw ref new Platform::NotImplementedException();
		//this->jsListener->inputResult((string)text);
	}

	void QspLib::setMute(Platform::Boolean flag)
	{
		this->jsListener->setMute((bool)flag);
	}

	void QspLib::setInputString(Platform::String ^ text)
	{
		throw ref new Platform::NotImplementedException();
		//this->jsListener->setInputString((string)text);
	}

	void QspLib::runInputString()
	{
		this->jsListener->runInputString();
	}

	void QspLib::runDefaultGame()
	{
		this->jsListener->runDefaultGame();
	}
}