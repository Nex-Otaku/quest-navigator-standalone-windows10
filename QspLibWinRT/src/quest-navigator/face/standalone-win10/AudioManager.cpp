#include "pch.h"
#include "AudioManager.h"
#include <string>
#include "..\..\core\dialogs.h"
#include "PlaybackListener.h"
#include "..\..\core\strings.h"
#include "..\..\core\configuration.h"

using namespace std;
using namespace Windows::Media::Playback;
using namespace Windows::Media::Core;
using namespace Windows::Foundation;

namespace QuestNavigator {
	AudioManager::AudioManager()
		: vecMusic(),
		muted(false),
		cacheEnabled(false),
		initedCritical(false),
		csMusicData()
	{
	}

	AudioManager::~AudioManager()
	{
	}

	void AudioManager::inject(
		PlaybackListener^ playbackListener,
		StringConverter* stringConverter
	)
	{
		this->playbackListener = playbackListener;
		this->stringConverter = stringConverter;
	}

	bool AudioManager::init()
	{
		showError("AudioManager::init");
		// Загружаем настройки
		cacheEnabled = Configuration::getBool(ecpSoundCacheEnabled);
		// Инициализируем структуру критической секции
		try {
			InitializeCriticalSection(&csMusicData);
		} catch (...) {
			showError("Не удалось проинициализировать структуру критической секции.");
			return false;
		}
		initedCritical = true;
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
		return true;
	}
	
	void AudioManager::deinit()
	{
		showError("AudioManager::deinit");
		// Высвобождаем структуру критической секции
		if (initedCritical) {
			DeleteCriticalSection(&csMusicData);
			initedCritical = false;
		}
	}

	void AudioManager::play(string file, int volume)
	{
		showError("AudioManager::play: [" + file + "] with volume " + std::to_string(volume));

		player = ref new MediaPlayer();

		player->SourceChanged += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
			playbackListener, &PlaybackListener::OnSourceChanged);

		player->MediaEnded += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
			playbackListener, &PlaybackListener::OnMediaEnded);

		player->MediaFailed += ref new TypedEventHandler<MediaPlayer^, Windows::Media::Playback::MediaPlayerFailedEventArgs^>(
			playbackListener, &PlaybackListener::OnMediaFailed);

		player->MediaOpened += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
			playbackListener, &PlaybackListener::OnMediaOpened);

		player->VolumeChanged += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
			playbackListener, &PlaybackListener::OnVolumeChanged);



		player->Source = MediaSource::CreateFromUri(ref new Uri(
			//"ms-appx:///game/standalone_content/music/EpicLoop.mp3"
			stringConverter->convertStdToUwp(
				getUriFromFileName("music/EpicLoop.mp3")
			)
		));
		player->Play();
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

	// *********************************************************
	//      Синхронизация потоков
	// *********************************************************

	// Входим в критическую секцию
	void AudioManager::lockMusicData()
	{
		try {
			EnterCriticalSection(&csMusicData);
		} catch (...) {
			showError("Не удалось войти в критическую секцию.");
		}
	}
	
	// Выходим из критической секции
	void AudioManager::unlockMusicData()
	{
		LeaveCriticalSection(&csMusicData);
	}

	// *********************************************************
	//      Прочее
	// *********************************************************

	string AudioManager::getUriFromFileName(string file)
	{
		return "ms-appx:///game/standalone_content/" + backslashToSlash(file);
	}
}