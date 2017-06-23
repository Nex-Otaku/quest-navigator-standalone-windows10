#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "..\..\core\dto\ErrorDto.h"
#include "..\..\platform\windows10\StringConverter.h"

using namespace std;

namespace QuestNavigator {
	class JsonSerializer
	{
	public:
		JsonSerializer();
		~JsonSerializer();

		void inject(
			StringConverter* stringConverter
		);

		string serializeGroupedContent(GroupedContentDto dto);
		// STUB

	private:
		StringConverter* stringConverter;
	};
}
