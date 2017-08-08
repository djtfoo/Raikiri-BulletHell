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

enum KEYCODE
{
    KEY_RIGHT = 0,
    KEY_LEFT,
    KEY_UP,
    KEY_DOWN,
    KEY_SPACE,
	KEY_ALT,
    KEY_SHIFT,
    KEY_R,

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

protected:
    Input() {}

    // keyboard
    static bool keys[KEYS_TOTAL];

    // Mouse
    static TOUCH_STATE mouseState[MOUSE_TOTAL];
    static Vec2 mousePos[MOUSE_TOTAL];

public:
    virtual ~Input() {}

    static void Init();

    // called by keyboard listener
    static void OnKeyPressed(KEYCODE keyCode);
    static void OnKeyReleased(KEYCODE keyCode);

    // called by mouse listener
    static void SetMouseState(TOUCH_TYPE type, TOUCH_STATE state);
    static void SetMousePos(TOUCH_TYPE type, Vec2 pos);

    static TOUCH_STATE GetTouchState(TOUCH_TYPE type);
    static Vec2 GetTouchPos(TOUCH_TYPE type);

    // user functions
    static KEYCODE EventKeyboardToKeycode(EventKeyboard::KeyCode keyCode);
    static bool IsKeyHeld(KEYCODE keyCode);
};

#endif