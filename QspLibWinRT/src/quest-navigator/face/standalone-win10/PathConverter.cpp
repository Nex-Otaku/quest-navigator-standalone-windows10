#include "pch.h"
#include "PathConverter.h"
#include <string>
#include "..\..\platform\windows10\ApplicationPathReader.h"

using namespace std;

namespace QuestNavigator {
	PathConverter::PathConverter()
	{
	}

	PathConverter::~PathConverter()
	{
	}

	void PathConverter::inject(ApplicationPathReader* applicationPathReader)
	{
		this->applicationPathReader = applicationPathReader;
	}

	// ��������������� ���������� ���� � �������������.
	// �������� ���: "D:\QuestNavigator\game\standalone_content\skins\gfx\my-image.png"
	// ����� ��������: "../standalone_content/skins/gfx/my-image.png"
	string PathConverter::convertAbsolutePathToRelative(string path)
	{
		// STUB
		return "";
	}
}