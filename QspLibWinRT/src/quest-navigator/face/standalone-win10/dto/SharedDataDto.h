#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	struct SharedDataDto
	{
		string str;
		int num;
		//JSValue jsValue; ������ ��� �������� ������ �� ���������� (�� ���� ����) � ���������.
		bool flag;
	};
}