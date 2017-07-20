#include"Player\pfunnel.h"
#include "AnimationHandler.h"
#include "Attack\Projectile.h"
pfunnel::pfunnel()
{
	_eSprite = Sprite::create("Blue_Back1.png");
	_eSprite->setScale(0.4);

	AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::SHIP_FUNNEL, true);
}

pfunnel::~pfunnel()
{

}
void pfunnel::RunAttack()
{
	auto delay = DelayTime::create(0.3f);
	Projectile* projectile = new Projectile();
	projectile->InitBasicBullet("Projectiles/ship_bullet.png", _eSprite->getPosition(), 3000, 1.f, false);
	_eSprite->runAction(CCSequence::create(delay, CallFunc::create(CC_CALLBACK_0(pfunnel::RunAttack, this)), NULL));
}

