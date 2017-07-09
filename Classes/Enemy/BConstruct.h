#include "WaveSpawner/Entity.h"
using namespace cocos2d;

class BConstruct : public Entity
{
public:
	BConstruct();
	~BConstruct();
	void SetData();
	void SettoSpawn();
	void SettoAttack();
	void SpawnFunnels();

protected:
	float timer;
	void DoAttack(float deltaatime);
	

};

