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
		// ��������� ���������
		cacheEnabled = Configuration::getBool(ecpSoundCacheEnabled);
		// �������������� ��������� ����������� ������
		try {
			InitializeCriticalSection(&csMusicData);
		} catch (...) {
			showError("�� ������� ������������������� ��������� ����������� ������.");
			return false;
		}
		initedCritical = true;
		return true;
	}
	
	void AudioManager::deinit()
	{
		showError("AudioManager::deinit");
		// ������������ ��������� ����������� ������
		if (initedCritical) {
			DeleteCriticalSection(&csMusicData);
			initedCritical = false;
		}
	}

	void AudioManager::play(string file, int volume)
	{
		showError("AudioManager::play: [" + file + "] with volume " + std::to_string(volume));


		if (file.length() == 0) {
			showError("�� ������ ��� ��������� �����");
			return;
		}
		
		// ���������, ������������� �� ��� ���� ����.
		// ���� �������������, ������ �� ������.
		// ���� ���� �����������, ������� ������������ ��� � ����� true,
		// ����� �� ������ ������ �� ���������.
		//if (checkPlayingFileSetVolume(file, true, volume))
		//	return;
		// !!! ������� ����������� !
		// �����, ����� ������ ������� �� ����������� ����������.
		
		string fullPath = getRightPath(file);
		// ��������� ������������� � ����������
		if (!fileSystemManager->fileExists(fullPath)) {
			showError("�� ������� ������� �������� ����: " + file);
			return;
		}
		
		if (endsWith(file, ".mid")) {
			//lockMusicData();
			//// ������� ������ �� ������ ������ MIDI.
			//// ����������� ������������ �� ����� ������ MIDI-����� ������������.
			//// �� ����� ���� ���� ����, ������� ���������� �������� ���� �� ������� ����� ���� ���.
			//for (int i = 0; i < (int)vecMusic.size(); i++)
			//{
			//	ContainerMusic& container = vecMusic[i];
			//	if (container.isMidi) {
			//		vecMusic.erase(vecMusic.begin() + i);
			//		break;
			//	}
			//}
		
			//// ��������� ���� � ������.
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
			sound->MediaFailed += ref new TypedEventHandler<MediaPlayer^, Windows::Media::Playback::MediaPlayerFailedEventArgs^>(
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
			
			// ��������� ���� � ������
			lockMusicData();
			float realVolume = 0;// getRealVolume(volume);
			//sound->setVolume(realVolume);
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
	//      ������������� �������
	// *********************************************************

	// ������ � ����������� ������
	void AudioManager::lockMusicData()
	{
		try {
			EnterCriticalSection(&csMusicData);
		} catch (...) {
			showError("�� ������� ����� � ����������� ������.");
		}
	}
	
	// ������� �� ����������� ������
	void AudioManager::unlockMusicData()
	{
		LeaveCriticalSection(&csMusicData);
	}
}