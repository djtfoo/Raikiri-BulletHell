#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include "Entity.h"
#include "WaveSpawner.h"
using namespace cocos2d;

class BConstruct : public Entity
{
public:
	BConstruct();
	~BConstruct();
	void SetData(float scale);
	void SettoSpawn();
	void SettoAttack();
	void SpawnFunnels();
	void UpdateHP();
	WaveSpawner* spawner;
	Sprite* BossHealthBarRed;
	Sprite* BossHealthBarGreen;
	Label* BossHealthNumber;


protected:
	float timer,prevt,spawntimer;
	bool islooped,finished;
	int counter;
	unsigned phase;
	float MaxHp;
	void DoAttack(float deltaatime);
	void ToggleWaypoint();
	void FirstAttack(float dt);
	void SecondAttack(float dt);
	void TriggerFinal();
	void P3Loop();
	

};

#endif  // CONSTRUCT_H