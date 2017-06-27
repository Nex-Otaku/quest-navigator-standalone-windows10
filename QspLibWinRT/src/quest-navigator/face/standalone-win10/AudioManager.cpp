#include "pch.h"
#include "AudioManager.h"
#include <string>
#include "..\..\core\dialogs.h"

using namespace std;
using namespace Windows::Media::Playback;

namespace QuestNavigator {
	AudioManager::AudioManager()
	{
	}

	AudioManager::~AudioManager()
	{
	}

	bool AudioManager::init()
	{
		showError("AudioManager::init");
		//// Загружаем настройки
		//cacheEnabled = Configuration::getBool(ecpSoundCacheEnabled);
		//// Инициализируем структуру критической секции
		//try {
		//	InitializeCriticalSection(&csMusicData);
		//} catch (...) {
		//	showError("Не удалось проинициализировать структуру критической секции.");
		//	return false;
		//}
		//initedCritical = true;
		//// Запускаем звуковую библиотеку
		//audioDevice = OpenDevice();
		//if (!audioDevice) {
		//	showError("Не удалось запустить звуковую подсистему");
		//	deinit();
		//	return false;
		//}
		//// Устанавливаем колбэк
		//StopCallbackPtr cbHolder = new AudiereStopCallbackHolder();
		//audioDevice->registerCallback(cbHolder.get());
		//return true;
	
		// STUB
		return true;
	}
	
	void AudioManager::deinit()
	{
		showError("AudioManager::deinit");
		// Высвобождаем структуру критической секции
		//if (initedCritical) {
		//	DeleteCriticalSection(&csMusicData);
		//	initedCritical = false;
		//}
	}

	void AudioManager::play(string file, int volume)
	{
		// STUB
		showError("AudioManager::play: [" + file + "] with volume " + std::to_string(volume));
		//MediaPlayer^ player = ref new MediaPlayer();
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