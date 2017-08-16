#pragma once

#include <string>
#include "cocos2d.h"
#include "EnemyData.h"

using namespace cocos2d;


class Explosion
{
private:

public:
	enum EXPLODE_TYPE
	{
		EX_CLEAR,
		EX_SMALL,
		EX_NULL
	};


	EXPLODE_TYPE _type;
	float DamagedRenderTimer;
	float DamagedRenderTempTimer;
	bool TakenDamage;
	Explosion();
	~Explosion();

	void GenerateExplosion(Vec2 pos,EXPLODE_TYPE type = EX_SMALL);
	void SelfDelete();
	void ScreenExplode();
	Sprite* _eSprite;
};
