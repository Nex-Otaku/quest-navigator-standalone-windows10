#include "pch.h"
#include "QspLib.h"

using namespace QuestNavigator;

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
	}

	// ������� �� ���������� � �������� API ������.

	// �� ���������� ����� int, bool, wchar_t
	// ��. �������
	// https://docs.microsoft.com/en-us/cpp/cppcx/fundamental-types-c-cx
	// �� ������� � �������� ��.
	// https://docs.microsoft.com/en-us/cpp/cppcx/type-system-c-cx

	void QspLib::restartGame()
	{
		this->jsListener->restartGame();
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