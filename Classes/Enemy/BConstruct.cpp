#include "BConstruct.h"
#include "BFunnel.h"
#include "AnimationHandler.h"
#include "Attack\Projectile.h"
BConstruct::BConstruct()
{
	timer = 0;
	islooped = false;
	phase = 2;
	counter = 0;
	prevt = 0;
	finished = false;
	spawntimer = 0;
}
BConstruct::~BConstruct()
{

}

void BConstruct::DoAttack(float dt)
{
	switch (phase)
	{
	case(1)://first pattern
		timer += dt;
		spawntimer += dt;
		if (spawntimer > 2)
		{
			SpawnFunnels();
			spawntimer = 0;
			FirstAttack(dt);
		
		}
		if (!islooped)
			ToggleWaypoint();

		
		break;
	case(2) ://second pattern
		timer += dt;
		spawntimer += dt;
		if (spawntimer > 2)
		{
			SpawnFunnels();
			spawntimer = 0;
			FirstAttack(dt);
			
		}
		else
		{
			SecondAttack(dt);
		}
		

		if (!islooped)
			ToggleWaypoint();

		break;

	case(3) :// beserk
		timer += dt;
		if (timer > 2)
		{
			SpawnFunnels();
			timer = 0;
		}
		if (!islooped)
			ToggleWaypoint();

		break;
	}



}

void BConstruct::SetData()
{
	_spawnPos = Vec2(4000, 500);
	_destination = Vec2(920, 500);
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
	

	auto moveTo = MoveTo::create(8, _destination);
	//_eSprite->runAction(moveTo);//simple moveto
	_eSprite->runAction(CCSequence::create(moveTo, CallFunc::create(CC_CALLBACK_0(Entity::SettoAttack, this)), NULL));//this is for the attack state
}

void BConstruct::SettoAttack()
{
	_active = true;

	//do sum attack code here


}

void BConstruct::SpawnFunnels()
{
	BFunnel* funnel = new BFunnel;
	Vec2 spawn;
	spawn.x = _eSprite->getPositionX() + cocos2d::RandomHelper::random_int(-250, 50);
	spawn.y = _eSprite->getPositionY() + cocos2d::RandomHelper::random_int(-150, 150);

	funnel->SetSpawn(spawn);
	Entity* ent = dynamic_cast<Entity*>(funnel);
	spawner->SpawnInEnemy(funnel);
}

void BConstruct::ToggleWaypoint()
{
	auto moveTo = MoveTo::create(4, Vec2(_destination.x, _destination.y+100));
	auto moveTo2 = MoveTo::create(4, Vec2(_destination.x, _destination.y-400));
	_eSprite->runAction(CCSequence::create(moveTo, moveTo2, CallFunc::create(CC_CALLBACK_0(BConstruct::ToggleWaypoint, this)),NULL));
	islooped = true;
}

void BConstruct::FirstAttack(float dt)
{
	int i = counter;
	if (timer - prevt > 0.07)
	{
		prevt = timer;
		counter++;

		Vec2 pos = _eSprite->getPosition();
		
		Projectile* projectile = new Projectile();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", Vec2(pos.x+i, pos.y-i*i), 300, Vec2(-1, 0).getNormalized());
		Projectile* projectile2 = new Projectile();
		projectile2->InitBasicBullet("Projectiles/enemy_bullet.png", Vec2(pos.x - i, -pos.y - i*i), 300, Vec2(-1, 0).getNormalized());
		//Projectile* projectile3 = new Projectile();
		//projectile3->InitBasicBullet("Projectiles/enemy_bullet.png", -pos, 100, Vec2(-1, 0));
		if (counter > 10)
			counter = 0;
			

	}


}

void BConstruct::SecondAttack(float dt)
{
	int i = counter*3;
	if (timer - prevt > 0.06)
	{
		prevt = timer;
		counter++;

		Vec2 pos = _eSprite->getPosition();
		Projectile* projectile = new Projectile();
		projectile->InitBasicBullet("Projectiles/enemy_bullet.png", Vec2(pos.x-120, pos.y-120+i), 300, Vec2(-1, i*0.1).getNormalized());
		Projectile* projectile2 = new Projectile();
		projectile2->InitBasicBullet("Projectiles/enemy_bullet.png", Vec2(pos.x+120, pos.y-120+i), 300, Vec2(-1, i*0.1).getNormalized());
		Projectile* projectile3 = new Projectile();
		projectile3->InitBasicBullet("Projectiles/enemy_bullet.png", Vec2(pos.x - 120+i, pos.y + 120), 300, Vec2(-1, i*0.1).getNormalized());
		Projectile* projectile4 = new Projectile();
		projectile4->InitBasicBullet("Projectiles/enemy_bullet.png", Vec2(pos.x -120+ i, pos.y - 120), 300, Vec2(-1, i*0.1).getNormalized());
	
		if (counter > 10)
			counter = 1;
	}
}
void squareup(Vec2 pos , int i)
{

}