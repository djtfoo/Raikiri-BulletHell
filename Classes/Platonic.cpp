#include "Platonic.h"
#include "Projectile.h"
#include "HelloWorldScene.h"

Platonic::Platonic()
{
	timer = 0;
	timer2 = 0;
	stream = false;
}

Platonic::~Platonic()
{

}

void Platonic::DoAttack(float dt)
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
	timer2 += dt;
	if (timer >0.8)
	{
		if (!stream)
			stream = true;
		else
			stream = false;
		for (int i = 0; i < 24; i++)
		{
			float deg = i * 15;
			deg = CC_DEGREES_TO_RADIANS(deg);
			
			Vec2 dir(cos(deg), sin(deg));
			//dir.y += i;
			Projectile* projectile = new Projectile();
			projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), dir.getNormalized(),3200,true,5);
		}
		timer = 0;
	}
	if (stream && timer2> 0.06)
	{
		auto scene = Director::getInstance()->getRunningScene();
		auto layer = scene->getChildByTag(999);
		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
		
		Vec2 displacement = helloLayer->mainPlayer->GetSprite()->getPosition()-this->GetSprite()->getPosition();
		Projectile* projectile = new Projectile();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), displacement.getNormalized(), 4700, true, 10);
		timer2 = 0;
	}

}