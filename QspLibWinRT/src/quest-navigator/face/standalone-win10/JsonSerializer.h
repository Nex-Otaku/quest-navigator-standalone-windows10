#pragma once

#include <string>
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "..\..\core\dto\ErrorDto.h"
#include "..\..\platform\windows10\StringConverter.h"
#include "..\..\core\dto\SkinDto.h"

using namespace std;
using namespace Windows::Data::Json;

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
		string serializeSaveSlots(SaveSlotsDto dto);
		string serializeError(ErrorDto dto);
		string serializeMenu(vector<MenuItemDto> menu);

	private:
		StringConverter* stringConverter;

		JsonObject^ getSkinObject(SkinDto dto);
	};
}
