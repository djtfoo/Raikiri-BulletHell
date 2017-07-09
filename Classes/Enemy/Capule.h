#include "WaveSpawner/Entity.h"
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

