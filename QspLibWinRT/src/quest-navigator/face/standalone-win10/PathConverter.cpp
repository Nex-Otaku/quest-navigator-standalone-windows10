#include "pch.h"
#include "PathConverter.h"
#include <string>
#include "..\..\platform\windows10\ApplicationPathReader.h"
#include "..\..\core\dialogs.h"
#include "..\..\core\strings.h"

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
		// "D:\QuestNavigator"
		string rootAppPath = applicationPathReader->getApplicationFolderPath();
		// "D:\QuestNavigator\game\"
		string gamePath = rootAppPath + "\\game\\";
		if (!startsWith(path, gamePath)) {
			showError("�� ������� ������������� ���� � �����.");
			return path;
		}

		size_t length = gamePath.size();
		// "standalone_content\skins\gfx\my-image.png"
		string tail = path.substr(length);

		// "../standalone_content/skins/gfx/my-image.png"
		string relativePath = "../" + backslashToSlash(tail);
		
		return relativePath;
	}
}