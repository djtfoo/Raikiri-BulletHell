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
	float timer;
	void DoAttack(float deltaatime);


};

#endif  // CAPULE_H