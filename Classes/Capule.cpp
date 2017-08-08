#include "capule.h"
#include "Projectile.h"

Capule::Capule()
{
	timer = 0;
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
	if (timer > 1.4)
	{
		Projectile* projectile = new Projectile();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), Vec2(-1, 0), 2000,true);
		timer = 0;
	}
}