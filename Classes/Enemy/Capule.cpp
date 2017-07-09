#include "capule.h"
#include "Attack/Projectile.h"
Capule::Capule()
{
	timer = 0;
}

Capule::~Capule()
{

}

void Capule::DoAttack(float dt)
{
	timer += dt;
	if (timer > 1.4)
	{
		Projectile* projectile = new Projectile();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), 300, Vec2(-1,0));
		timer = 0;
	}
}