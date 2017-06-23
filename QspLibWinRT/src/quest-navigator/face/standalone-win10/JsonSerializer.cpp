#include "pch.h"
#include "JsonSerializer.h"
#include <string>

using namespace std;
using namespace Windows::Data::Json;

namespace QuestNavigator {
	JsonSerializer::JsonSerializer()
	{
	}

	JsonSerializer::~JsonSerializer()
	{
	}

	void JsonSerializer::inject(StringConverter* stringConverter)
	{
		this->stringConverter = stringConverter;
	}

	string JsonSerializer::serializeGroupedContent(GroupedContentDto dto)
	{
		JsonObject^ jsonObject = ref new JsonObject();

		//jsonObject->Insert();
		return string();
	}
}