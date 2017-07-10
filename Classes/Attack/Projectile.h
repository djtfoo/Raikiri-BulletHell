#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "cocos2d.h"
#include <string>
using std::string;
using namespace cocos2d;
class Projectile
{
private:
	//Sprite* ProjectileSprite;
	float ProjectileSpeed;
public:

	Sprite* InitBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime,bool isEnemy);
	Sprite* InitBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, Vec2 direction, bool isEnemy);

	Sprite* InitLaserBullet(string LaserImg, Vec2 SpawnPosition);

	Sprite* getProjectileSprite();
	void setProjectileSprite(Sprite* ProjectileSprite);



};





#endif