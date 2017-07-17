#ifndef __FREEZETIME_SCENE_H__
#define __FREEZETIME_SCENE_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

class FreezeTime : public Layer
{
private:
    //Label* descriptionLabel;

    Sprite* playerDash;
    Sprite* playerDashLine;

    Sprite* rendtexSprite;

    int drawCount;

    bool freezeTimeDone;

    float drawPointTimer;

public:
    static cocos2d::Scene* createScene(Sprite* rendtexSprite);

    virtual bool init();

    // callback functions
    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onMouseDown(Event*);
    virtual void onMouseMove(Event*);
    virtual void onMouseUp(Event*);

    static std::vector<Vec2> dashLinePoints;

    void update(float dt);
    //bool isKeyHeld(EventKeyboard::KeyCode keyCode);

    Size playingSize;

    // implement the "static create()" method manually
    CREATE_FUNC(FreezeTime);
};

#endif // __MAINMENU_SCENE_H__
