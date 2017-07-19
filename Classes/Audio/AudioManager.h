#ifndef AUDIOMANAGER_H_
#define AUDIOMANAGER_H_

#include "SimpleAudioEngine.h"
#include <map>
#include <string>

using std::map;
using std::string;

class AudioManager
{
private:
    CocosDenshion::SimpleAudioEngine* audioEngine;
    map<string, string> SFXList;
    map<string, string> BGMList;

    bool LoadFile(const char* file_path);
    void PreloadAudio(int fileType, string audioName, string fileName);

    std::map<string, int> loopSFXID;  // return ID for playing SFX (used for stopping SFX loops) - key is name of SFX

public:
    ~AudioManager(){}

    static AudioManager* GetInstance()
    {
        static AudioManager am;
        return &am;
    };

    void Init();
    void PlaySoundEffect(string soundName, bool loop = false);
    void PlayBackgroundMusic(string musicName, bool loop = true);

    //void PauseBackgroundMusic();
    //void ResumeBackgroundMusic();
    void StopBackgroundMusic();
    void StopSoundEffect(string soundName);

    void ApplicationDidEnterBackground();
    void ApplicationWillEnterForeground();
};



#endif