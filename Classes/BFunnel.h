#ifndef FUNNEL_H
#define FUNNEL_H

#include "Entity.h"
using namespace cocos2d;

class BFunnel : public Entity
{
public:
	BFunnel();
	~BFunnel();
	void SetSpawn(Vec2 pos);
	void SettoAttack();

protected:
	float timer;
	void Attack();
	void Fire();
};

#endif  // FUNNEL_H