#include "pch.h"
#include "PathConverter.h"
#include <string>

using namespace std;

namespace QuestNavigator {
	PathConverter::PathConverter()
	{
	}

	PathConverter::~PathConverter()
	{
	}

	// ��������������� ���������� ���� � �������������.
	// �������� ���: "D:\QuestNavigator\game\standalone_content\skins\gfx\my-image.png"
	// ����� ��������: "../standalone_content/skins/gfx/my-image.png"
	string PathConverter::convertAbsolutePathToRelative(string path)
	{
		// STUB
	}
}