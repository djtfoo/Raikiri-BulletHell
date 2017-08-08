#ifndef PLATONIC_H
#define PLATONIC_H

#include "Entity.h"
using namespace cocos2d;

class Platonic : public Entity
{
public:
	Platonic();
	~Platonic();

protected:
	float timer;
	void DoAttack(float deltaatime);


};

#endif  // PLATONIC_H