#include "pch.h"
#include "ApplicationPathReader.h"
#include <string>

using namespace std;

namespace QuestNavigator {
	ApplicationPathReader::ApplicationPathReader()
	{
	}

	ApplicationPathReader::~ApplicationPathReader()
	{
	}

	void ApplicationPathReader::inject(StringConverter* stringConverter)
	{
		this->stringConverter = stringConverter;
	}

	string ApplicationPathReader::getApplicationFolderPath()
	{
		Windows::ApplicationModel::Package^ package = Windows::ApplicationModel::Package::Current;
		Windows::Storage::StorageFolder^ installedLocation = package->InstalledLocation;

		Platform::String^ path = installedLocation->Path;
		return stringConverter->convertUwpToStd(path);
	}
}
