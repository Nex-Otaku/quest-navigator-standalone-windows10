#pragma once

using namespace Windows::Media::Playback;

namespace QuestNavigator {
	ref class PlaybackListener sealed
	{
	public:
		PlaybackListener();

		void OnSourceChanged(MediaPlayer^, Platform::Object^);
	};
}
