#ifndef ATTACK_H_
#define ATTACK_H_


#include <string>
#include "cocos2d.h"
#include "Projectile.h"
using std::string;
using namespace cocos2d;

class Attack
{


private:
	string BulletImg;


	Sprite* LaserSprite;
	bool InitLaser;
public:
	Attack();
	~Attack();


	void FireBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime);
	void FireLaserBullet(string LaserImg, Vec2 SpawnPosition);
	void StopFiringLaser(float LaserSpeed, float LifeTime);
	void LaserUpdate(float dt, float LaserScaleX, Vec2 PlayerPosition);
	bool GetInitLaser();
	void SetInitLaser(bool setlaser);

	Sprite* GetLaserSprite();
	void SetLaserSprite(Sprite* laser);
};




#endif