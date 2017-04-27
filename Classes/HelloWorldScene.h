#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*); 

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void update(float dt);


	Size playingSize;
	
	Sprite *bg_sprite1, *bg_sprite2;
	bool currbg;
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
