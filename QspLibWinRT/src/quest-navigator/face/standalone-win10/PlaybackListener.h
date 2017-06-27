#pragma once

using namespace Windows::Media::Playback;

namespace QuestNavigator {
	ref class PlaybackListener sealed
	{
	public:
		PlaybackListener();

		void OnSourceChanged(MediaPlayer^, Platform::Object^);
		void OnMediaEnded(MediaPlayer^, Platform::Object^);
		void OnMediaFailed(MediaPlayer^, MediaPlayerFailedEventArgs^);
		void OnMediaOpened(MediaPlayer^, Platform::Object^);
		void OnVolumeChanged(MediaPlayer^, Platform::Object^);
	};
}
