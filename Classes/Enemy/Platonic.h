#include "WaveSpawner/Entity.h"
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

