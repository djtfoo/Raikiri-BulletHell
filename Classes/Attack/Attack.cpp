#include "Attack.h"
#include "Projectile.h"
#include "../Scenes/HelloWorldScene.h"
#include "../Audio/AudioManager.h"

#define COCOS2D_DEBUG 1
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

    AudioManager::GetInstance()->PlaySoundEffect("Bullet");
}
void  Attack::FireLaserBullet(string LaserImg, Vec2 SpawnPosition)
{
	if (!InitLaser)
	{
		Projectile* projectile = new Projectile();
		LaserSprite = projectile->InitLaserBullet(LaserImg, SpawnPosition);
		this->InitLaser = true;

        AudioManager::GetInstance()->PlaySoundEffect("Laser");
        AudioManager::GetInstance()->PlaySoundEffect("LaserHum", true);
	}
	/*else
	{
		LaserSprite->setScaleX(LaserSprite->getScaleX() + LaserScaleX);
	}*/
}
void  Attack::StopFiringLaser(/*float LaserSpeed,float LifeTime*/)
{
    if (this->InitLaser) {
        this->InitLaser = false;
        //auto moveEvent = MoveBy::create(LifeTime, Vec2(1.f, 0.f) * LaserSpeed);
        //LaserSprite->runAction(moveEvent);

        LaserSprite->removeFromParentAndCleanup(true);
        LaserSprite = NULL;

        AudioManager::GetInstance()->StopSoundEffect("LaserHum");
    }

}
void Attack::LaserUpdate(float dt, float LaserScaleX,Vec2 PlayerPosition)
{
    if (InitLaser)
    {
        for (map<Entity*, Node*>::iterator it = EntityLaserDamageList.begin(); it != EntityLaserDamageList.end(); it++)
        {
            it->first->_hp -= 0.1f;
            if (it->first->_hp <= 0)
            {
                auto scene = Director::getInstance()->getRunningScene();
                auto layer = scene->getChildByTag(999);
                HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
                helloLayer->waveSpawner->DestroyEnemy(it->second);

                it->second->removeFromParentAndCleanup(true);
                EntityLaserDamageList.erase(it);
                break;
            }
        }
        if (LaserSprite) {
            LaserSprite->setPosition(PlayerPosition);
          //  LaserSprite->getPhysicsBody()->onAdd();
        }
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
void Attack::AddToLaserVector(Entity* entity, Node* node)
{
    bool NotInVector = true;
    for (map<Entity*, Node*>::iterator it = EntityLaserDamageList.begin(); it != EntityLaserDamageList.end(); it++)
    {
        if (it->first == entity)
        {
            NotInVector = false;
            break;
        }
    }
    if (NotInVector)
    {
        EntityLaserDamageList.insert(EntityLaserDamageList.begin(), std::pair<Entity*, Node*>(entity, node));
    }
}
void Attack::DeleteFromLaserVector(Entity* entity)
{
    int a = 0;
    for (map<Entity*, Node*>::iterator it = EntityLaserDamageList.begin(); it != EntityLaserDamageList.end(); it++)
    {
        if (it->first == entity)
        {
            EntityLaserDamageList.erase(it);
            break;
        }
        a++;
    }

}

// Special Attack Dash
void Attack::SetDashLinePoints(const std::vector<Vec2>& points)
{
    dashLinePoints = points;
}