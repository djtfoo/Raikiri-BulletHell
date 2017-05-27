#ifndef PLAYER_H
#define PLAYER_H

#include "../Input/Input.h"
#include "cocos2d.h"

using namespace cocos2d;

class Player
{
private:
	int lives;
	bool b_shooting;
	//int score;

	// shader stuff
	Vec2 mLoc;
	Vec2 mLocInc;
	GLProgram* charEffect;
	
	Sprite* mainSprite;
	int intDirX, intDirY;	// direction just to determine +ve or -ve movement
	float fSpeed;

public:
	void Init(const char* imgSource, const char* playerName, float X, float Y);
	void Update(float dt);
	void AnimatePlayer(KEYCODE key);	// KEY_INPUT for direction
	void StopAnimation();

	void SetMoveCharX(int dirX);	// keyboard
	void SetMoveCharY(int dirY);	// keyboard
	void MoveCharByCoord(float X, float Y);		// mouse

	Sprite* GetSprite(void)
	{
		return mainSprite;
	}
};

#endif