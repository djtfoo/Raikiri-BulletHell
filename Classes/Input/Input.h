/****************************************************************************

\file	Input.h
\author Jing Ting
\brief
Accessible information regarding keyboard, mouse and touch input from the user

****************************************************************************/

#ifndef INPUT_H
#define INPUT_H

#include "cocos2d.h"

using namespace cocos2d;

enum KEY_INPUT
{
    KEY_RIGHT = 0,
    KEY_LEFT,
    KEY_UP,
    KEY_DOWN,

    KEYS_TOTAL
};

enum TOUCH_TYPE
{
    TOUCH_MOUSELEFT = 0,
    TOUCH_MOUSERIGHT,

    MOUSE_TOTAL
};

enum TOUCH_STATE
{
    TOUCH_NIL,
    TOUCH_HELD,
    TOUCH_RELEASED
};

class Input : public cocos2d::Layer
{
private:
    Input() {}
    ~Input() {}

    // keyboard
    bool keys[KEYS_TOTAL];

    // Mouse
    TOUCH_STATE mouseState[MOUSE_TOTAL];
    Vec2 mousePos[MOUSE_TOTAL];

public:
    static Input* GetInstance()
    {
        static Input input;
        return &input;
    };

    void Init();
    void Update(float dt);

    // called by keyboard listener
    void OnKeyPressed(KEY_INPUT keyCode);
    void OnKeyReleased(KEY_INPUT keyCode);

    // called by mouse listener
    void SetMouseState(TOUCH_TYPE type, TOUCH_STATE state);
    void SetMousePos(TOUCH_TYPE type, Vec2 pos);

    TOUCH_STATE GetTouchState(TOUCH_TYPE type);
    Vec2 GetTouchPos(TOUCH_TYPE type);

    // user functions
    bool IsKeyHeld(KEY_INPUT keyCode);
};

#endif