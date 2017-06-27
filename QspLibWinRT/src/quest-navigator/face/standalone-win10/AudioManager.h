#pragma once

#include <string>
#include "PathConverter.h"
#include "PlaybackListener.h"

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
			PathConverter* pathConverter,
			PlaybackListener^ playbackListener
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
		PathConverter* pathConverter;
		PlaybackListener^ playbackListener;


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
