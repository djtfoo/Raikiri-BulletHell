#ifndef CAPULE_H
#define CAPULE_H

#include "Entity.h"
using namespace cocos2d;

class Capule : public Entity
{
public:
	Capule();
	~Capule();

protected:
	Vec2 target;
	float timer;
	int count, countmax;
	void DoAttack(float deltaatime);
	bool lock;

};

#endif  // CAPULE_H