#pragma once

#include <string>
#include <vector>
#include "SkinDto.h"

using namespace std;

namespace QuestNavigator
{
	struct GroupedContentDto
	{
		struct act {
			string image;
			string desc;
		};

		struct obj {
			string image;
			string desc;
			int selected;
		};

		SkinDto skin;
		string main;
		int scrollmain;
		vector<act> acts;
		string vars;
		vector<obj> objs;
		string js;

		bool skinPrepared;
		bool mainDescPrepared;
		bool actsPrepared;
		bool objsPrepared;
		bool varsDescPrepared;
		bool jsCmdPrepared;
	};
}