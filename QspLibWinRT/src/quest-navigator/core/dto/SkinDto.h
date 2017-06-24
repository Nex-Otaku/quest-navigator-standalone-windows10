#pragma once

#include <string>

using namespace std;

namespace QuestNavigator
{
	struct SkinDto
	{
		int hideScrollAny;
		int hideScrollArrows;
		int hideScrollMain;
		int hideScrollActs;
		int hideScrollVars;
		int hideScrollObjs;

		int useHtml;
		int noSave;
		int disableScroll;
		int viewAlwaysShow;
		int isStandalone;

		int showActs;
		int showVars;
		int showObjs;
		int showInput;

		string msgTextFormat;
		string inputTextFormat;
		string mainDescTextFormat;
		string varsDescTextFormat;
	};
}