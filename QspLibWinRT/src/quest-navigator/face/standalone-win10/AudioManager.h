#pragma once

#include <string>
#include "PlaybackListener.h"
#include "..\..\platform\windows10\StringConverter.h"

using namespace std;
using namespace Windows::Media::Playback;

namespace QuestNavigator {
	//public delegate void OnSourceChanged();

	class AudioManager
	{
		struct ContainerMusic {
			string name; // ���� � ����� - �����, ��� ����� � ����
			int volume;
			bool isMidi;
			//OutputStreamPtr sound;
		};
	public:
		AudioManager();
		~AudioManager();

		void inject(
			PlaybackListener^ playbackListener,
			StringConverter* stringConverter
		);

		bool init();
		void deinit();
		void play(string file, int volume);
		bool isPlaying(string file);
		void closeAll();
		void close(string file);
		void mute(bool toBeMuted);

		void OnSourceChanged(MediaPlayer^, Platform::Object^);
	private:
		PlaybackListener^ playbackListener;
		StringConverter* stringConverter;


		MediaPlayer^ player;

		vector<ContainerMusic> vecMusic;
		bool muted;
		bool cacheEnabled;
		
		bool checkPlayingFileSetVolume(string file, bool setVolume, int volume);
		float getRealVolume(int volume);
		
		// ������������� �������
		bool initedCritical;
		// ��������� ��� ����������� ������
		CRITICAL_SECTION csMusicData;
		// ������ � ����������� ������
		void lockMusicData();
		// ������� �� ����������� ������
		void unlockMusicData();



		string getUriFromFileName(string file);
	};
}
