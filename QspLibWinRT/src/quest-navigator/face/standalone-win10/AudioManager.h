#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {
	class AudioManager
	{
	public:
		AudioManager();
		~AudioManager();

		//bool init();
		//void deinit();
		void play(string file, int volume);
		bool isPlaying(string file);
		void closeAll();
		void close(string file);
		void mute(bool toBeMuted);
	};
}
