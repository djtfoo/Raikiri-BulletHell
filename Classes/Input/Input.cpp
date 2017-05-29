#include "Input.h"

USING_NS_CC;

// keyboard
bool Input::keys[KEYS_TOTAL];

// Mouse
TOUCH_STATE Input::mouseState[MOUSE_TOTAL];
Vec2 Input::mousePos[MOUSE_TOTAL];


void Input::Init()
{
    for (KEYCODE i = static_cast<KEYCODE>(0); i < KEYS_TOTAL; i = static_cast<KEYCODE>(i + 1))
    {
        keys[i] = false;
    }

    for (TOUCH_TYPE i = static_cast<TOUCH_TYPE>(0); i < MOUSE_TOTAL; i = static_cast<TOUCH_TYPE>(i + 1))
    {
        mouseState[i] = TOUCH_NIL;
        mousePos[i].setZero();
    }
}

// KEYBOARD CONTROLS
void Input::OnKeyPressed(KEYCODE keyCode)
{
    keys[keyCode] = true;
}

void Input::OnKeyReleased(KEYCODE keyCode)
{
    keys[keyCode] = false;
}

bool Input::IsKeyHeld(KEYCODE keyCode)
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

KEYCODE Input::EventKeyboardToKeycode(EventKeyboard::KeyCode keyCode)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        return KEY_RIGHT;

    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        return KEY_LEFT;

    case EventKeyboard::KeyCode::KEY_UP_ARROW:
        return KEY_UP;

    case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        return KEY_DOWN;

    case EventKeyboard::KeyCode::KEY_SPACE:
        return KEY_SPACE;

    case EventKeyboard::KeyCode::KEY_R:
        return KEY_R;

	case EventKeyboard::KeyCode::KEY_ALT:
		return KEY_ALT;

    case EventKeyboard::KeyCode::KEY_SHIFT:
        return KEY_SHIFT;

    default:
        return KEYS_TOTAL;
    }

}