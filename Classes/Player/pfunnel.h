#pragma once
#include <string>
#include "cocos2d.h"

using namespace cocos2d;


class pfunnel
{
private:
	//bullet type
public:

	float firedebounce;
	pfunnel();
	~pfunnel();
	void RunAttack();
	void stopAttack();
	int number;
	bool _active;
	Sprite* _eSprite;
};
