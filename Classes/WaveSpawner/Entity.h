#pragma once

#include <string>
#include "cocos2d.h"
#include "EnemyData.h"

using namespace cocos2d;


class Entity
{
private:
	enum ENEMY_TYPE
	{
		CAPULE,
		PLATONIC,
		NUM_TYPE
	};


	ENEMY_TYPE _type;
	Vec2 _spawnPos;
	Vec2 _destination;
	Vec2 _exitDestination;
	

	

	
	//bullet type
public:
	Entity();
	~Entity();

	void SettoSpawn();
	void SettoDespawn();
	void SettoAttack();

	void SetEntity(EnemyData data);
	void SetInactive();
	void SetActive();
	virtual void DoAttack(float dt);

	//game related vairables
	int _waveNum;
	int _hp;
	bool _active;
	Sprite* _eSprite;
};
