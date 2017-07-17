#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player/Player.h"
#include "WaveSpawner/WaveSpawner.h"
#include "LightEffect/LightEffect.h"
#include "GUI\GUI.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
private:
    GLProgram* proPostProcess;
    RenderTexture* rendtex;
    Sprite* rendtexSprite;
	Node* spriteNode;
    Node* projectieNode;
	LightEffect* lightEffect;

	GUI* playerGui;

    bool timeStopped;
	bool freezeAnimationChange;
    bool freezeAttack;
    float freezeAttackTimer;

    Vec2 screenMin, screenMax;
    float xPos, yPos;
    float widthX, heightY;
    //float minX, maxX, minY, maxY;

    void UpdateFreezeAnimation(float dt);
    void UpdateFreezeAttack(float dt);

public:
	enum GO_TYPE
	{
		PLAYER=0,
		PLAYERPROJ=1,
		ENEMY=2,
		ENEMYPROJ=3,
		POWERUP=4,
        PLAYERSHIELD=5,
        ENEMYSHIELD=6,
		LASERPOWERUP=7,
	};
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // callback functions
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);
    virtual void onMouseDown(Event*);
    virtual void onMouseUp(Event*);
	virtual bool onContactBegin(PhysicsContact& contact);
    virtual bool onContactSeparate(PhysicsContact& contact);
	/*virtual bool onContactPreSolve(PhysicsContact& contact);
	virtual bool onContactPostSolve(PhysicsContact& contact);*/
	//virtual void tick(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void update(float dt);

    // For Special Attack
    void ExecuteFreezeTime();
    void SetPlayerDashPoints(const std::vector<Vec2>& points);

    //bool isKeyHeld(EventKeyboard::KeyCode keyCode);

	Size playingSize;
	
    // World objects
    Player* mainPlayer;
    //Player* GetPlayer() { return mainPlayer; }

	Node* getSpriteNode();
    Node* getProjectileNode();
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
