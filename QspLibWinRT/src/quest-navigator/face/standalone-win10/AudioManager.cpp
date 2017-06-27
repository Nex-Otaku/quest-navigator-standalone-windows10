#include "pch.h"
#include "AudioManager.h"
#include <string>
#include "..\..\core\dialogs.h"

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
		showError("AudioManager::play: [" + file + "] with volume " + std::to_string(volume));
	}

	bool AudioManager::isPlaying(string file)
	{
		// STUB
		showError("AudioManager::isPlaying: [" + file + "]");
		return true;
	}

	void AudioManager::closeAll()
	{
		// STUB
		showError("AudioManager::closeAll");
	}

	void AudioManager::close(string file)
	{
		// STUB
		showError("AudioManager::close: [" + file + "]");
	}

	void AudioManager::mute(bool toBeMuted)
	{
		// STUB
		showError("AudioManager::mute");
	}
}