#include "pch.h"
#include "AudioManager.h"
#include <string>

using namespace std;

namespace QuestNavigator {
	AudioManager::AudioManager()
	{
	}

	AudioManager::~AudioManager()
	{
	}

	void AudioManager::play(string file, int volume)
	{
		// STUB
	}

	bool AudioManager::isPlaying(string file)
	{
		// STUB
		return false;
	}

	void AudioManager::closeAll()
	{
		// STUB
	}

	void AudioManager::close(string file)
	{
		// STUB
	}

	void AudioManager::mute(bool toBeMuted)
	{
		// STUB
	}
}