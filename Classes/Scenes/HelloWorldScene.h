#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include "WaveSpawner/WaveSpawner.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
    GLProgram* proPostProcess;
    RenderTexture* rendtex;
    Sprite* rendtexSprite;
	Node* spriteNode;

    bool timeStopped;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // callback functions
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onMouseDown(Event*);
    virtual void onMouseUp(Event*);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void update(float dt);
    void FreezeTime();
    //bool isKeyHeld(EventKeyboard::KeyCode keyCode);

	Size playingSize;
	
    // World objects
    Player* mainPlayer;
    Player* GetPlayer();

	Node* getSpriteNode();

    // Enemy stuff
    WaveSpawner* waveSpawner;

	Sprite *bg_sprite1, *bg_sprite2;
	bool currbg;
	// implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	private:
	cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char *format, int count);
};

#endif // __HELLOWORLD_SCENE_H__
