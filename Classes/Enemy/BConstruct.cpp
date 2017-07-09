#include "BConstruct.h"
#include "AnimationHandler.h"
BConstruct::BConstruct()
{
	timer = 0;

}
BConstruct::~BConstruct()
{

}

void BConstruct::DoAttack(float dt)
{
	timer += dt;
	if (timer > 4)
	{
		SpawnFunnels();
	}
}

void BConstruct::SetData()
{
	_spawnPos = Vec2(1000, 500);
	_destination = Vec2(700, 500);
	//_exitDestination = data._exitDestination;
	_type = BCONSTRUCT;

	//_eSprite->setAnchorPoint(Vec2::ZERO);
	//SetActive();
}

void BConstruct::SettoSpawn()
{
	_eSprite->setScale(1.5);
	_eSprite->setPosition(_spawnPos.x, _spawnPos.y);
	//AnimHandler::getInstance()->setAnimation(this_eSprite, AnimHandler::CAPULE_SPAWN, true);

	 AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::CONSTRUCT_ACTIVE, true);
	

	auto moveTo = MoveTo::create(1, _destination);
	//_eSprite->runAction(moveTo);//simple moveto
	auto setactive = CallFunc::create([this](){SettoAttack(); });
	_eSprite->runAction(CCSequence::create(moveTo, CallFunc::create(CC_CALLBACK_0(Entity::SettoAttack, this)), NULL));//this is for the attack state
}

void BConstruct::SettoAttack()
{
	_active = true;

	//do sum attack code here


}

void BConstruct::SpawnFunnels()
{

}