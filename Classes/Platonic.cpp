#include "Platonic.h"
#include "Projectile.h"

Platonic::Platonic()
{
	timer = 0;
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
	if (timer > 1.2)
	{
		for (int i = 0; i < 3; i++)
		{
			Vec2 dir(-3, -1);
			dir.y += i;
			Projectile* projectile = new Projectile();
			projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), dir.getNormalized(),1200,true,10);
		}
		timer = 0;
	}
}