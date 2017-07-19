#ifndef ATTACK_H_
#define ATTACK_H_


#include <string>
#include <map>
#include "cocos2d.h"
#include "Projectile.h"
#include "WaveSpawner\Entity.h"
using std::string;
using std::map;
using namespace cocos2d;

class Attack
{


private:
	string BulletImg;

    map<Entity*, Node*> EntityLaserDamageList;
	Sprite* LaserSprite;
	bool InitLaser;

    std::vector<Vec2> dashLinePoints;   // for special attack

public:
	Attack();
	~Attack();


    void SetDashLinePoints(const std::vector<Vec2>& points);

	void FireBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime,bool isEnemy);
	void FireLaserBullet(string LaserImg, Vec2 SpawnPosition);
	void StopFiringLaser(/*float LaserSpeed, float LifeTime*/);
	void LaserUpdate(float dt, float LaserScaleX, Vec2 PlayerPosition);
	bool GetInitLaser();
	void SetInitLaser(bool setlaser);

	Sprite* GetLaserSprite();
	void SetLaserSprite(Sprite* laser);

    void AddToLaserVector(Entity* entity, Node* node);
    void DeleteFromLaserVector(Entity* entity);
};




#endif