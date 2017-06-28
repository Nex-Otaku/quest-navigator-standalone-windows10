#include "pch.h"
#include "AudioManager.h"
#include <string>
#include "..\..\core\dialogs.h"
#include "PlaybackListener.h"
#include "..\..\core\strings.h"
#include "..\..\core\configuration.h"
#include "..\..\core\files.h"
#include "PathConverter.h"
#include "FileSystemManager.h"
#include "..\..\platform\windows10\StringConverter.h"

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
		StringConverter* stringConverter,
		FileSystemManager* fileSystemManager,
		PathConverter* pathConverter
	)
	{
		this->playbackListener = playbackListener;
		this->stringConverter = stringConverter;
		this->fileSystemManager = fileSystemManager;
		this->pathConverter = pathConverter;
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
		if (file.length() == 0) {
			showError("Не задано имя звукового файла");
			return;
		}
		
		// Проверяем, проигрывается ли уже этот файл.
		// Если проигрывается, устанавливаем громкость.
		// Если файл не проигрывается и закэширован, перезапускаем его.
		// Нужно, чтобы список плееров не разрастался бесконечно.
		bool foundPlaying = false;
		lockMusicData();
		for (int i = 0; i < (int)vecMusic.size(); i++)
		{
			ContainerMusic& it = vecMusic[i];
			if (it.name == file)
			{
				if (it.isMidi) {
					//foundPlaying = MidiService::isPlaying(it.name);
					//if (foundPlaying)
					//{
					//	it.volume = volume;
					//	MidiService::setVolume(volume);
					//}
				} else {
					foundPlaying = cacheEnabled || isPlayingState(it.sound->PlaybackSession->PlaybackState);
					if (foundPlaying) {
						it.volume = volume;
						it.sound->Volume = getRealVolume(volume);

						// Если файл уже не проигрывается, но остался в кэше,
						// запускаем проигрывание.
						// Трек по завершению был отмотан на начало,
						// поэтому просто вызываем play().
						if (cacheEnabled && !isPlayingState(it.sound->PlaybackSession->PlaybackState)) {
							it.sound->Play();
						}
					}
				}
				break;
			}
		}
		unlockMusicData();
		if (foundPlaying) {
			return;
		}
		
		string fullPath = getRightPath(file);
		// Проверяем существование и читаемость
		if (!fileSystemManager->fileExists(fullPath)) {
			showError("Не удалось открыть звуковой файл: " + file);
			return;
		}
		
		if (endsWith(file, ".mid")) {
			//lockMusicData();
			//// Очищаем список от других файлов MIDI.
			//// Допускается прогигрывать не более одного MIDI-файла одновременно.
			//// Мы найдём лишь один файл, поэтому достаточно прогнать цикл по вектору всего один раз.
			//for (int i = 0; i < (int)vecMusic.size(); i++)
			//{
			//	ContainerMusic& container = vecMusic[i];
			//	if (container.isMidi) {
			//		vecMusic.erase(vecMusic.begin() + i);
			//		break;
			//	}
			//}
		
			//// Добавляем файл в список.
			//MidiService::play(file, volume);
			//ContainerMusic container;
			//container.isMidi = true;
			//container.name = file;
			//container.volume = volume;
			//vecMusic.push_back(container);
			//unlockMusicData();
		} else {
			MediaPlayer^ sound = ref new MediaPlayer();
			sound->SourceChanged += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
				playbackListener, &PlaybackListener::OnSourceChanged);
			sound->MediaEnded += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
				playbackListener, &PlaybackListener::OnMediaEnded);
			sound->MediaFailed += ref new TypedEventHandler<MediaPlayer^, MediaPlayerFailedEventArgs^>(
				playbackListener, &PlaybackListener::OnMediaFailed);
			sound->MediaOpened += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
				playbackListener, &PlaybackListener::OnMediaOpened);
			sound->VolumeChanged += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
				playbackListener, &PlaybackListener::OnVolumeChanged);
			sound->Source = MediaSource::CreateFromUri(ref new Uri(
				stringConverter->convertStdToUwp(
					pathConverter->absolutePathToUri(file)
				)
			));
			
			// Добавляем файл в список
			lockMusicData();
			sound->Volume = getRealVolume(volume);
			sound->Play();
			ContainerMusic container;
			container.isMidi = false;
			container.name = file;
			container.volume = volume;
			container.sound = sound;
			vecMusic.push_back(container);
			unlockMusicData();
		}
	}

	bool AudioManager::isPlaying(string file)
	{
		showError("AudioManager::isPlaying: [" + file + "]");

		if (file.length() == 0) {
			return false;
		}
			
		bool foundPlaying = false;
		lockMusicData();
		for (int i = 0; i < (int)vecMusic.size(); i++)
		{
			ContainerMusic& it = vecMusic[i];
			if (it.name == file)
			{
				if (it.isMidi) {
					// foundPlaying = MidiService::isPlaying(it.name);
				} else {
					if (cacheEnabled) {
						// Цикл состояний:
						// Opening -> Buffering -> Playing -> Paused
						foundPlaying = isPlayingState(it.sound->PlaybackSession->PlaybackState);
					} else {
						foundPlaying = true;
					}
				}
				break;
			}
		}
		unlockMusicData();
		return foundPlaying;
	}

	void AudioManager::closeAll()
	{
		showError("AudioManager::closeAll");
		lockMusicData();
		for (int i = 0; i < (int)vecMusic.size(); i++)
		{
			ContainerMusic& container = vecMusic[i];
			if (container.isMidi) {
				//MidiService::close(closeAll, file);
			} else {
				if (isPlayingState(container.sound->PlaybackSession->PlaybackState)) {
					container.sound->Pause();
				}
				if (cacheEnabled) {
					// Устанавливаем трек на начало
					TimeSpan position;
					position.Duration = 0;
					container.sound->PlaybackSession->Position = position;
				} else {
					// Высвобождаем память
					delete container.sound;
					container.sound = nullptr;
				}
			}
		}
		if (!cacheEnabled) {
			vecMusic.clear();
		}
		unlockMusicData();
	}

	void AudioManager::close(string file)
	{
		showError("AudioManager::close: [" + file + "]");
		if ((int)file.length() == 0) {
			return;
		}
			
		lockMusicData();
		for (int i = 0; i < (int)vecMusic.size(); i++)
		{
			ContainerMusic& container = vecMusic[i];
			if (container.name != file) {
				continue;
			}
			if (container.isMidi) {
				//MidiService::close(closeAll, file);
				//vecMusic.erase(vecMusic.begin() + i);
				//break;
			} else {
				if (isPlayingState(container.sound->PlaybackSession->PlaybackState)) {
					container.sound->Pause();
				}
				if (cacheEnabled) {
					// Устанавливаем трек на начало
					TimeSpan position;
					position.Duration = 0;
					container.sound->PlaybackSession->Position = position;
				} else {
					// Высвобождаем память
					delete container.sound;
					container.sound = nullptr;
				}
				if (!cacheEnabled) {
					vecMusic.erase(vecMusic.begin() + i);
				}
				break;
			}
		}
		unlockMusicData();
	}

	void AudioManager::mute(bool toBeMuted)
	{
		showError("AudioManager::mute");
		lockMusicData();
		muted = toBeMuted;
		for (int i = 0; i < (int)vecMusic.size(); i++)
		{
			ContainerMusic& container = vecMusic[i];
			if (container.isMidi) {
				//MidiService::mute(toBeMuted);
				//MidiService::setVolume(container.volume);
			} else {
				container.sound->Volume = getRealVolume(container.volume);
			}
		}
		unlockMusicData();
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

	// Проверка на проигрывание.
	bool AudioManager::isPlayingState(MediaPlaybackState state)
	{
		// Цикл состояний:
		// Opening -> Buffering -> Playing -> Paused
		return (state == MediaPlaybackState::Opening)
			|| (state == MediaPlaybackState::Buffering)
			|| (state == MediaPlaybackState::Playing);
	}
	
	double AudioManager::getRealVolume(int volume)
	{
		double result = 0;
		if (!muted) {
			result = ((double)volume) / 100;
		} else {
			result = 0;
		}
			
		return result;
	}
}