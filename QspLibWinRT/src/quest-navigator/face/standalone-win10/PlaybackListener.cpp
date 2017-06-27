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
		showError("OnSourceChanged");
	}
	
	void PlaybackListener::OnMediaEnded(MediaPlayer^ player, Platform::Object^ object)
	{
		showError("OnMediaEnded");
	}
	
	void PlaybackListener::OnMediaFailed(MediaPlayer^ player, MediaPlayerFailedEventArgs^ args)
	{
		showError("OnMediaFailed");
	}
	
	void PlaybackListener::OnMediaOpened(MediaPlayer^ player, Platform::Object^ object)
	{
		showError("OnMediaOpened");
	}
	
	void PlaybackListener::OnVolumeChanged(MediaPlayer^ player, Platform::Object^ object)
	{
		showError("OnVolumeChanged");
	}
}