#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include "cocos2d.h"
#include <map>
#include <string>

using namespace cocos2d;
using std::map;
using std::string;

class AudioManager
{
private:
	map<string, string>* SoundList;

public:
	~AudioManager(){}

	static AudioManager* GetInstance()
	{
		static AudioManager am;
		return &am;
	};

	void Init();
	void PlaySoundEffect(string SoundName, bool loop);
	void PlayBackGroundMusic(string MusicName, bool loop);
	void PreloadAudio(string SoundName, string FileName);
	
};



#endif