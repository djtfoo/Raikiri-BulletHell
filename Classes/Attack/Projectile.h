#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "cocos2d.h"
#include <string>
using std::string;
using namespace cocos2d;
class Projectile
{
private:
    Sprite* ProjectileSprite;
    float ProjectileSpeed;
public:

    Sprite* InitBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime, bool isEnemy);//this is pretty much player exclusive
    Sprite* InitBasicBullet(string BulletImg, Vec2 SpawnPosition, Vec2 direction, float BulletSpeed,  bool isEnemy,float LifeTime=8);//uses move to, useful for enemies;
	Sprite* InitMissile(Vec2 SpawnPosition, Vec2 velocity, float lifetime = 6);
	Sprite* InitComplexBullet(string BulletImg, Vec2 SpawnPosition, Vec2 velocity, float BulletSpeed,  bool isEnemy, bool gravity = false, float lifetime = 6);//general usage, takes velocity*speed;
   
	void InitLaserBullet(Sprite* laserSprite, Size size, Node* spriteNode);
    void SetLaserBullet(Sprite* laserSprite, Vec2 SpawnPosition);

    Sprite* getProjectileSprite();
    void setProjectileSprite(Sprite* ProjectileSprite);



};





#endif