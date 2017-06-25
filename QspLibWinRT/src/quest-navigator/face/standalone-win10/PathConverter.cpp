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

	// Преобразовываем абсолютный путь в относительный.
	// Исходный вид: "D:\QuestNavigator\game\standalone_content\skins\gfx\my-image.png"
	// Нужно получить: "../standalone_content/skins/gfx/my-image.png"
	string PathConverter::convertAbsolutePathToRelative(string path)
	{
		// STUB
	}
}