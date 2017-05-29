#include "Audio\AudioManager.h"
#include <fstream>
#include <sstream>

void AudioManager::Init()
{
    audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
    LoadFile("Audio/audiofiles.txt");
}

bool AudioManager::LoadFile(const char* file_path)
{
    std::ifstream fileStream(file_path, std::ios::binary);
    if (!fileStream.is_open()) {
        return false;
    }

    //================
    // READ FILE DATA
    //================
    while (!fileStream.eof())
    {
        std::string thisLine;
        std::getline(fileStream, thisLine);

        if (thisLine == "" || thisLine[0] == '#')   // empty line OR comment
            continue;

        std::stringstream dataStream(thisLine);
        std::string data;

        // first content is file type - BGM or SFX
        std::getline(dataStream, data, ',');
        int fileType = std::stoi(data);

        // second content is reference name to the audio file
        std::getline(dataStream, data, ',');
        string audioName = data;

        // third content is file path
        std::getline(dataStream, data, ',');
        string filePath = data;

        // preload & add to list
        PreloadAudio(fileType, audioName, filePath);
    }

    fileStream.close();

    return true;
}

void AudioManager::PreloadAudio(int fileType, string audioName, string fileName)
{
    fileName = "Audio/" + fileName;

    if (fileType == 0) {
        audioEngine->preloadBackgroundMusic(fileName.c_str());
        BGMList.insert(std::pair<string, string>(audioName, fileName));
    }
    else if (fileType == 1) {
        audioEngine->preloadEffect(fileName.c_str());
        SFXList.insert(std::pair<string, string>(audioName, fileName));
    }
}

void AudioManager::PlaySoundEffect(string soundName, bool loop)
{
    map<string, string>::iterator it = SFXList.find(soundName);
    if (it != SFXList.end())
        audioEngine->playEffect(it->second.c_str(), loop);
}

void AudioManager::PlayBackgroundMusic(string musicName, bool loop)
{
    //if (audioEngine->isBackgroundMusicPlaying())
    //    audioEngine->stopBackgroundMusic();

    map<string, string>::iterator it = BGMList.find(musicName);
    if (it != BGMList.end())
        audioEngine->playBackgroundMusic(it->second.c_str(), loop);
}

void AudioManager::PauseBackgroundMusic()
{

}

void AudioManager::ResumeBackgroundMusic()
{

}

void AudioManager::StopBackgroundMusic()
{

}

// functions called by AppDelegate
void AudioManager::ApplicationDidEnterBackground()
{
    audioEngine->pauseAllEffects();
    audioEngine->pauseBackgroundMusic();
}

void AudioManager::ApplicationWillEnterForeground()
{
    audioEngine->resumeAllEffects();
    audioEngine->resumeBackgroundMusic();
}