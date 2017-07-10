#include "BFunnel.h"
#include "AnimationHandler.h"
#include "Attack\Projectile.h"
BFunnel::BFunnel()
{
	timer = 0;
}
BFunnel::~BFunnel()
{

}
void BFunnel::SetSpawn(Vec2 pos)
{
	_eSprite->setPosition(pos);
	_type = BFUNNEL;
	auto setactive = CallFunc::create(CC_CALLBACK_0(BFunnel::SettoAttack, this));
	AnimHandler::GetInstance()->setCCAnimation(_eSprite, AnimHandler::CONSTRUCTFUNNEL_SPAWN,setactive);
	//_eSprite->runAction(moveTo);//simple moveto
}

void BFunnel::SettoAttack()
{
	_active = true;
	AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::CONSTRUCTFUNNEL_ACTIVE,true);
	Attack();
}
void BFunnel::Attack()
{
	auto delay = DelayTime::create(0.5f);
	_eSprite->runAction(CCSequence::create(delay, CallFunc::create(CC_CALLBACK_0(BFunnel::Fire, this)), CallFunc::create(CC_CALLBACK_0(BFunnel::Attack, this)), NULL));
}

void BFunnel::Fire()
{
		Projectile* projectile = new Projectile();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", _eSprite->getPosition(), 300, Vec2(-1, 0),true);
		timer = 0;
}