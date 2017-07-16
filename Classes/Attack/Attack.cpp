#include "Attack.h"
#include "Projectile.h"




Attack::Attack()
{
	InitLaser = false;
}

Attack::~Attack()
{




}
void Attack::FireBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime,bool isEnemy)
{
	Projectile* projectile = new Projectile();
	/*Sprite* ProjectileSprite =*/ projectile->InitBasicBullet(BulletImg, SpawnPosition, BulletSpeed, LifeTime, isEnemy);
}
void  Attack::FireLaserBullet(string LaserImg, Vec2 SpawnPosition)
{
	if (!InitLaser)
	{
		Projectile* projectile = new Projectile();
		LaserSprite = projectile->InitLaserBullet(LaserImg, SpawnPosition);
		this->InitLaser = true;
	}
	/*else
	{
		LaserSprite->setScaleX(LaserSprite->getScaleX() + LaserScaleX);
	}*/
}
void  Attack::StopFiringLaser(float LaserSpeed,float LifeTime)
{
    if (this->InitLaser) {
        this->InitLaser = false;
        auto moveEvent = MoveBy::create(LifeTime, Vec2(1.f, 0.f) * LaserSpeed);
        LaserSprite->runAction(moveEvent);
    }

}
void Attack::LaserUpdate(float dt, float LaserScaleX,Vec2 PlayerPosition)
{
	if (InitLaser)
	{
		//LaserSprite->getPhysicsBody()->getFirstShape()->
		/*LaserSprite->getPhysicsBody()->getShape()->
		LaserSprite->setScaleX(LaserSprite->getScaleX() + LaserScaleX);*/
		LaserSprite->setPosition(PlayerPosition);
	}
}
bool  Attack::GetInitLaser()
{
	return InitLaser;
}
void  Attack::SetInitLaser(bool setlaser)
{
	this->InitLaser = setlaser;
}
Sprite* Attack::GetLaserSprite()
{
	return LaserSprite;
}
void Attack::SetLaserSprite(Sprite* laser)
{
	this->LaserSprite = laser;
}