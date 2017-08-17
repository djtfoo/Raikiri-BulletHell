#ifndef __FACEBOOK_SCENE_H__
#define __FACEBOOK_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class FacebookScene : public cocos2d::Layer
{
private:

    bool touchBegan;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // callback functions
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);

    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event * event);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void update(float dt);
    //bool isKeyHeld(EventKeyboard::KeyCode keyCode);

    Size playingSize;

    Sprite *bg_sprite;
    // implement the "static create()" method manually
    CREATE_FUNC(FacebookScene);
};

#endif // __MAINMENU_SCENE_H__
