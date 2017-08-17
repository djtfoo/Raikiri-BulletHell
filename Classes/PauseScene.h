#pragma once
#ifndef __PAUSESCENE_SCENE_H__
#define __PAUSESCENE_SCENE_H__

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

class PauseScene : public Layer
{
private:
	//Label* descriptionLabel;

	Label* ResumeText;
	Label* ExitText;
	//Sprite* playerDash;
	//Sprite* playerDashLine;

	Sprite* ResumeButton;
	Sprite* ExitButton;
	//Sprite* rendtexSprite;

	//int drawCount;

	//bool touchBegan;
	//bool PauseSceneDone;
	bool ExitSelected;

	///float drawPointTimer;
	
	
public:
	static cocos2d::Scene* createScene(Sprite* rendtexSprite);
	float dashDistance;
	float maxDashDistance;

	virtual bool init();
	const float currentWidth = 1920;
	const float currentHeight = 1080;
	// callback functions
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event*);
	//virtual void onMouseDown(Event*);
	//virtual void onMouseMove(Event*);
	//virtual void onMouseUp(Event*);

	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event * event);
	void onTouchEnded(Touch* touch, Event * event);

	//static std::vector<Vec2> dashLinePoints;
	//static bool chargeUsed;
	
	void update(float dt);
	//bool isKeyHeld(EventKeyboard::KeyCode keyCode);
	float GetScreenHeightPercentage(float percentage)
	{
		return playingSize.height *(percentage / 100);
	}
	float  GetScreenWidthPercentage(float percentage)
	{
		return playingSize.width *(percentage / 100);
	}
	float ScaleWithScreen()
	{
		return (Director::getInstance()->getWinSizeInPixels().height / currentHeight);
	}
	Size playingSize;

	// implement the "static create()" method manually
	CREATE_FUNC(PauseScene);
};

#endif // __MAINMENU_SCENE_H__
