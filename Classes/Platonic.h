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
	float timer,timer2;
	void DoAttack(float deltaatime);
	bool stream;

};

#endif  // PLATONIC_H