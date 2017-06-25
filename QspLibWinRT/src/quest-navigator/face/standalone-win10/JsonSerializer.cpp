#include "pch.h"
#include "JsonSerializer.h"
#include <string>
#include "..\..\core\skin.h"
#include "..\..\core\dto\SaveSlotsDto.h"
#include "..\..\core\dto\GroupedContentDto.h"
#include "..\..\core\dto\MenuItemDto.h"
#include "..\..\core\dto\ErrorDto.h"
#include "..\..\core\dto\SkinDto.h"

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
		JsonObject^ root = ref new JsonObject();

		if (dto.skinPrepared) {
			JsonObject^ skin = getSkinObject(dto.skin);
			root->Insert("skin", skin);
		}

		if (dto.mainDescPrepared) {
			JsonValue^ main = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.main));
			root->Insert("main", main);

			JsonValue^ scrollmain = JsonValue::CreateNumberValue(dto.scrollmain);
			root->Insert("scrollmain", scrollmain);
		}

		if (dto.actsPrepared) {
			JsonArray^ acts = ref new JsonArray();
			for (size_t i = 0; i < dto.acts.size(); i++) {
				JsonObject^ act = ref new JsonObject();

				// image
				JsonValue^ image = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.acts[i].image));
				act->Insert("image", image);

				// desc
				JsonValue^ desc = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.acts[i].desc));
				act->Insert("desc", desc);

				acts->Append(act);
			}
			root->Insert("acts", acts);
		}

		if (dto.varsDescPrepared) {
			JsonValue^ vars = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.vars));
			root->Insert("vars", vars);
		}

		if (dto.objsPrepared) {
			JsonArray^ objs = ref new JsonArray();
			for (size_t i = 0; i < dto.objs.size(); i++) {
				JsonObject^ obj = ref new JsonObject();

				// image
				JsonValue^ image = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.objs[i].image));
				root->Insert("image", image);

				// desc
				JsonValue^ desc = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.objs[i].desc));
				root->Insert("desc", desc);

				// selected
				JsonValue^ selected = JsonValue::CreateNumberValue(dto.objs[i].selected);
				root->Insert("selected", selected);

				objs->Append(obj);
			}
			root->Insert("objs", objs);
		}

		if (dto.jsCmdPrepared) {
			JsonValue^ js = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.js));
			root->Insert("js", js);
		}

		Platform::String^ serialized = root->ToString();
		return stringConverter->convertUwpToStd(serialized);
	}

	string JsonSerializer::serializeSaveSlots(SaveSlotsDto dto)
	{
		JsonObject^ root = ref new JsonObject();

		int open = dto.open ? 1 : 0;
		root->Insert("open", JsonValue::CreateNumberValue(open));

		JsonArray^ slots = ref new JsonArray();
		for (size_t i = 0; i < dto.slots.size(); i++) {
			JsonValue^ slot = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.slots[i]));
			slots->Append(slot);
		}
		root->Insert("slots", slots);

		Platform::String^ serialized = root->ToString();
		return stringConverter->convertUwpToStd(serialized);
	}

	string JsonSerializer::serializeError(ErrorDto dto)
	{
		JsonObject^ root = ref new JsonObject();

		JsonValue^ desc = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.desc));
		root->Insert("desc", desc);

		JsonValue^ loc = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.loc));
		root->Insert("loc", loc);

		root->Insert("actIndex", JsonValue::CreateNumberValue(dto.actIndex));

		root->Insert("line", JsonValue::CreateNumberValue(dto.line));

		Platform::String^ serialized = root->ToString();
		return stringConverter->convertUwpToStd(serialized);
	}

	string JsonSerializer::serializeMenu(vector<MenuItemDto> menu)
	{
		JsonArray^ menuList = ref new JsonArray();
		for (size_t i = 0; i < menu.size(); i++) {
			JsonObject^ menuItem = ref new JsonObject();

			JsonValue^ desc = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(menu[i].desc));
			menuItem->Insert("desc", desc);

			JsonValue^ image = JsonValue::CreateStringValue(stringConverter->convertStdToUwp(menu[i].image));
			menuItem->Insert("image", image);

			menuList->Append(menuItem);
		}

		Platform::String^ serialized = menuList->ToString();
		return stringConverter->convertUwpToStd(serialized);
	}

	JsonObject^ JsonSerializer::getSkinObject(SkinDto dto)
	{
		JsonObject^ skin = ref new JsonObject();

		skin->Insert("hideScrollAny", JsonValue::CreateNumberValue(dto.hideScrollAny));
		skin->Insert("hideScrollArrows", JsonValue::CreateNumberValue(dto.hideScrollArrows));
		skin->Insert("hideScrollMain", JsonValue::CreateNumberValue(dto.hideScrollMain));
		skin->Insert("hideScrollActs", JsonValue::CreateNumberValue(dto.hideScrollActs));
		skin->Insert("hideScrollVars", JsonValue::CreateNumberValue(dto.hideScrollVars));
		skin->Insert("hideScrollObjs", JsonValue::CreateNumberValue(dto.hideScrollObjs));
		skin->Insert("useHtml", JsonValue::CreateNumberValue(dto.useHtml));
		skin->Insert("noSave", JsonValue::CreateNumberValue(dto.noSave));
		skin->Insert("disableScroll", JsonValue::CreateNumberValue(dto.disableScroll));
		skin->Insert("viewAlwaysShow", JsonValue::CreateNumberValue(dto.viewAlwaysShow));
		skin->Insert("isStandalone", JsonValue::CreateNumberValue(dto.isStandalone));
		skin->Insert("showActs", JsonValue::CreateNumberValue(dto.showActs));
		skin->Insert("showVars", JsonValue::CreateNumberValue(dto.showVars));
		skin->Insert("showObjs", JsonValue::CreateNumberValue(dto.showObjs));
		skin->Insert("showInput", JsonValue::CreateNumberValue(dto.showInput));

		skin->Insert("msgTextFormat", JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.msgTextFormat)));
		skin->Insert("inputTextFormat", JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.inputTextFormat)));
		skin->Insert("mainDescTextFormat", JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.mainDescTextFormat)));
		skin->Insert("varsDescTextFormat", JsonValue::CreateStringValue(stringConverter->convertStdToUwp(dto.varsDescTextFormat)));

		return skin;
	}
}