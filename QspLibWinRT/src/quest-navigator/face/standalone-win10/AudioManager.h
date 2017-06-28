#pragma once

#include <string>
#include "PlaybackListener.h"
#include "..\..\platform\windows10\StringConverter.h"
#include "FileSystemManager.h"
#include "PathConverter.h"

using namespace std;
using namespace Windows::Media::Playback;

namespace QuestNavigator {
	class AudioManager
	{
		struct ContainerMusic {
			string name; // ���� � ����� - �����, ��� ����� � ����
			int volume;
			bool isMidi;
			//OutputStreamPtr sound;
			MediaPlayer^ sound;
		};
	public:
		AudioManager();
		~AudioManager();

		void inject(
			PlaybackListener^ playbackListener,
			StringConverter* stringConverter,
			FileSystemManager* fileSystemManager,
			PathConverter* pathConverter
		);

		bool init();
		void deinit();
		void play(string file, int volume);
		bool isPlaying(string file);
		void closeAll();
		void close(string file);
		void mute(bool toBeMuted);

	private:
		PlaybackListener^ playbackListener;
		StringConverter* stringConverter;
		FileSystemManager* fileSystemManager;
		PathConverter* pathConverter;

		MediaPlayer^ player;

		vector<ContainerMusic> vecMusic;
		bool muted;
		bool cacheEnabled;
		
		//bool checkPlayingFileSetVolume(string file, bool setVolume, int volume);
		//float getRealVolume(int volume);
		
		// ������������� �������
		bool initedCritical;
		// ��������� ��� ����������� ������
		CRITICAL_SECTION csMusicData;
		// ������ � ����������� ������
		void lockMusicData();
		// ������� �� ����������� ������
		void unlockMusicData();

		// �������� �� ������������.
		bool isPlayingState(MediaPlaybackState state);
	};
}
