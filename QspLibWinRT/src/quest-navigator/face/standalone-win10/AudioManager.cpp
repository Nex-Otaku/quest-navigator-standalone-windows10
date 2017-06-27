#include "pch.h"
#include "AudioManager.h"
#include <string>
#include "..\..\core\dialogs.h"

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

	void AudioManager::inject(PathConverter* pathConverter)
	{
		this->pathConverter = pathConverter;
	}

	bool AudioManager::init()
	{
		showError("AudioManager::init");
		//// ��������� ���������
		//cacheEnabled = Configuration::getBool(ecpSoundCacheEnabled);
		//// �������������� ��������� ����������� ������
		//try {
		//	InitializeCriticalSection(&csMusicData);
		//} catch (...) {
		//	showError("�� ������� ������������������� ��������� ����������� ������.");
		//	return false;
		//}
		//initedCritical = true;
		//// ��������� �������� ����������
		//audioDevice = OpenDevice();
		//if (!audioDevice) {
		//	showError("�� ������� ��������� �������� ����������");
		//	deinit();
		//	return false;
		//}
		//// ������������� ������
		//StopCallbackPtr cbHolder = new AudiereStopCallbackHolder();
		//audioDevice->registerCallback(cbHolder.get());
		//return true;
	
		// STUB
		return true;
	}
	
	void AudioManager::deinit()
	{
		showError("AudioManager::deinit");
		// ������������ ��������� ����������� ������
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
		
		
		//player->SourceChanged += ref new TypedEventHandler<MediaPlayer^, Platform::Object^>(
		//		this, &AudioManager::OnSourceChanged);



		player->Source = MediaSource::CreateFromUri(ref new Uri(
			//"ms-appx:///Assets/example_video.mkv"
			"ms-appx:///game/standalone_content/music/EpicLoop.mp3"
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