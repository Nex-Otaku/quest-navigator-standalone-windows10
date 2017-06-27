#include "pch.h"
#include "AudioManager.h"
#include <string>
#include "..\..\core\dialogs.h"
#include "PlaybackListener.h"

using namespace std;
using namespace Windows::Media::Playback;
using namespace Windows::Media::Core;
using namespace Windows::Foundation;

namespace QuestNavigator {
	AudioManager::AudioManager()
	{
	}

	AudioManager::~AudioManager()
	{
	}

	void AudioManager::inject(
		PathConverter* pathConverter,
		PlaybackListener^ playbackListener
	)
	{
		this->pathConverter = pathConverter;
		this->playbackListener = playbackListener;
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
		MediaPlayer^ player = ref new MediaPlayer();

		//Windows::Media::Playback::
		//player->SourceChanged += ref new Windows::Foundation::EventHandler<
		//	Windows::UI::Core::SourceChangedEventArgs^>(
		//		this, &AudioManager::OnSourceChanged);
		//}
		//Windows::Media::Playback::MediaPlayerDataReceivedEventArgs
		//Windows::Media::Playback::MediaPlayerSourceChangedEventArgs
		
		
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
			//"ms-appx:///Assets/example_video.mkv"
			"ms-appx:///game/standalone_content/music/EpicLoop.mp3"
			//"ms-appx:///../standalone_content/music/EpicLoop.mp3"
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

	void AudioManager::OnSourceChanged(MediaPlayer^ player, Platform::Object^ object)
	{
		// STUB
	}

	string AudioManager::getUriFromFileName(string file)
	{

		return string();
	}
}