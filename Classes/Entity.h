#pragma once

#include <string>
#include "cocos2d.h"
#include "EnemyData.h"

using namespace cocos2d;


class Entity
{
private:
	//bullet type
public:
	enum ENEMY_TYPE
	{
		CAPULE,
		PLATONIC,
		BCONSTRUCT,
		BFUNNEL,
		NUM_TYPE
	};


	ENEMY_TYPE _type;
	Vec2 _spawnPos;
	Vec2 _destination;
	Vec2 _exitDestination;
	float DamagedRenderTimer;
	float DamagedRenderTempTimer;
	bool TakenDamage;
	Entity();
	~Entity();

	virtual void SettoSpawn();
	void SettoDespawn();
	virtual void SettoAttack();

	virtual void SetEntity(EnemyData data);
	void SetInactive();
	void SetActive();
	Sprite* GetSprite();
	virtual void DoAttack(float dt);
	
    void TakeDamage(int dmg);
    bool IsDead();

	//game related vairables
	int _waveNum;
	float _hp;
	bool _active;
	Sprite* _eSprite;
};
