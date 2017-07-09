#include "WaveSpawner\Entity.h"
#include "WaveSpawner\WaveSpawner.h"
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
	WaveSpawner* spawner;

protected:
	float timer,prevt,spawntimer;
	bool islooped,finished;
	int counter;
	unsigned phase;
	void DoAttack(float deltaatime);
	void ToggleWaypoint();
	void FirstAttack(float dt);
	void SecondAttack(float dt);

};

