/****************************************************************************

\file	GameInputManager.h
\author Jing Ting
\brief
Singleton to process Input information to handle game mechanics

****************************************************************************/
#ifndef __GAMEINPUT_H__
#define __GAMEINPUT_H__

#include "Player/Player.h"
#include "Input.h"
#include <string>
#include <map>

using std::string;
using std::map;

class GameInputManager : public Input
{
private:
    GameInputManager() {}

    map<string, KEYCODE> keyControls;

public:
    virtual ~GameInputManager() {}

    static GameInputManager* GetInstance()
    {
        static GameInputManager input;
        return &input;
    };
    void Init();

    // called by keyboard listener
    void WhenKeyPressed(KEYCODE keyCode, Player* player);
    void WhenKeyReleased(KEYCODE keyCode, Player* player);

    bool IsKeyHeld(string key);
};

#endif