#include "pch.h"
#include "PlaybackListener.h"
#include "..\..\core\dialogs.h"

using namespace Windows::Media::Playback;

namespace QuestNavigator {
	PlaybackListener::PlaybackListener()
	{
	}

	void PlaybackListener::OnSourceChanged(MediaPlayer^ player, Platform::Object^ object)
	{
		//throw ref new Platform::NotImplementedException();
		showError("OnSourceChanged");
	}
}