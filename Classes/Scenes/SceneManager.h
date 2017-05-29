#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include <string>
#include <map>

#include "cocos2d.h"

using namespace cocos2d;

using std::string;
using std::map;

class SceneManager
{
private:
    map<string, cocos2d::Scene*> listOfScenes;

    SceneManager() {}

public:
    ~SceneManager() {}

    static SceneManager* GetInstance()
    {
        static SceneManager sm;
        return &sm;
    };

    void Init();
    void ChangeScene(string name);
    void Exit();
};

#endif