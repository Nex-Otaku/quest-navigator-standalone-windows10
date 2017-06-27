#pragma once

#include <string>

using namespace std;

namespace QuestNavigator {
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

		bool init();
		void deinit();
		void play(string file, int volume);
		bool isPlaying(string file);
		void closeAll();
		void close(string file);
		void mute(bool toBeMuted);

	private:
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
	};
}
