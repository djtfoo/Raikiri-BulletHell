#include "Input.h"

USING_NS_CC;

void Input::Init()
{
    for (KEY_INPUT i = static_cast<KEY_INPUT>(0); i < KEYS_TOTAL; i = static_cast<KEY_INPUT>(i + 1))
    {
        keys[i] = false;
    }

    for (TOUCH_TYPE i = static_cast<TOUCH_TYPE>(0); i < MOUSE_TOTAL; i = static_cast<TOUCH_TYPE>(i + 1))
    {
        mouseState[i] = TOUCH_NIL;
        mousePos[i].setZero();
    }
}

void Input::Update(float dt)
{

}

// KEYBOARD CONTROLS
void Input::OnKeyPressed(KEY_INPUT keyCode)
{
    keys[keyCode] = true;
}

void Input::OnKeyReleased(KEY_INPUT keyCode)
{
    keys[keyCode] = false;
}

bool Input::IsKeyHeld(KEY_INPUT keyCode)
{
    if (keys[keyCode])
        return true;

    return false;
}

// MOUSE CONTROLS
void Input::SetMouseState(TOUCH_TYPE touchtype, TOUCH_STATE state)
{
    mouseState[touchtype] = state;
}

void Input::SetMousePos(TOUCH_TYPE touchtype, Vec2 pos)
{
    mousePos[touchtype] = pos;
}

TOUCH_STATE Input::GetTouchState(TOUCH_TYPE touchtype)
{
    return mouseState[touchtype];
}

Vec2 Input::GetTouchPos(TOUCH_TYPE touchtype)
{
    return mousePos[touchtype];
}