#include "capule.h"
#include "Projectile.h"
#include "HelloWorldScene.h"
Capule::Capule()
{
	timer = 0;
	lock = false;
	count = 0;
	countmax = 8;
}

Capule::~Capule()
{

}

void Capule::DoAttack(float dt)
{
	if (TakenDamage)
	{
		DamagedRenderTempTimer += dt;
		if (DamagedRenderTempTimer <= DamagedRenderTimer)
		{
			if (_eSprite->getOpacity() != 0)
				_eSprite->setOpacity(100);
		}
		else
		{
			_eSprite->setOpacity(255);
			TakenDamage = false;
			DamagedRenderTempTimer = 0;
		}
	}
	timer += dt;
	if (timer > 1.4 && !lock)
	{
		auto scene = Director::getInstance()->getRunningScene();
		auto layer = scene->getChildByTag(999);
		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
		target = helloLayer->mainPlayer->GetSprite()->getPosition();
		lock = true;
		Projectile* projectile = new Projectile();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), Vec2(-1, 0.2), 2000,true);
		Projectile* projectile2 = new Projectile();
		projectile2->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), Vec2(-1, -0.2), 2000, true);
		timer = 0;
	}
	if (lock && timer > 0.06)
	{
		count++;
		if (count == countmax)
		{
			lock = false;
			timer = 0;
			count = 0;
		}
		Projectile* projectile = new Projectile();
		Vec2 displacement = target - this->GetSprite()->getPosition();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", Vec2(_eSprite->getPositionX()+ cocos2d::RandomHelper::random_int(-60, 60), _eSprite->getPositionY()+ cocos2d::RandomHelper::random_int(-60, 60)), displacement.getNormalized(), 5000, true);
	}
}