#include "BConstruct.h"
#include "BFunnel.h"
#include "AnimationHandler.h"
#include "Attack\Projectile.h"
#include "../Scenes/HelloWorldScene.h"
#define COCOS2D_DEBUG 1
BConstruct::BConstruct()
{
	timer = 0;
	islooped = false;
	phase = 1;
	counter = 0;
	prevt = 0;
	finished = false;
	spawntimer = 0;
	_hp = 1000;
	BossHealthBarRed=Sprite::create("GUI/BossHealthBarRed.png");
	BossHealthBarGreen=Sprite::create("GUI/BossHealthBarGreen.png");

	/*auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	
	SpriteNode->addChild(BossHealthBarRed, 1);
	SpriteNode->addChild(BossHealthBarGreen, 1);*/
	
	
	BossHealthBarGreen->setPosition(Vec2(300,400));
	BossHealthBarRed->setPosition(Vec2(300, 400));
	BossHealthBarGreen->setAnchorPoint(Vec2::ZERO);
	BossHealthBarRed->setAnchorPoint(Vec2::ZERO);
	BossHealthBarGreen->setScaleY(0.5f);
	BossHealthBarRed->setScaleY(0.5f);
	BossHealthBarGreen->setScaleX(200);
	BossHealthBarRed->setScaleX(200);
	MaxHp = _hp;
	BossHealthNumber = Label::createWithTTF(std::to_string(static_cast<int>(_hp)) + "/" + std::to_string(static_cast<int>(MaxHp)), "fonts/Batman.ttf", 24);
	BossHealthNumber->setColor(cocos2d::Color3B(0, 0, 0));
	BossHealthNumber->setPosition(500, 420);

	_eSprite->addChild(BossHealthBarRed, 0);
	_eSprite->addChild(BossHealthBarGreen, 0);
	_eSprite->addChild(BossHealthNumber, 0);
	//SpriteNode->addChild(BossHealthNumber, 1);


}
BConstruct::~BConstruct()
{

}

void BConstruct::DoAttack(float dt)
{
	UpdateHP();
	if (TakenDamage)
	{
		DamagedRenderTempTimer += dt;
		if (DamagedRenderTempTimer <= DamagedRenderTimer)
		{
			if (_eSprite->getOpacity() != 0)
				_eSprite->setOpacity(0);
		}
		else
		{
			_eSprite->setOpacity(255);
			TakenDamage = false;
			DamagedRenderTempTimer = 0;
		}
	}
	switch (phase)
	{
	case(1)://first pattern
		timer += dt;
		spawntimer += dt;
		if (spawntimer > 2)
		{
			SpawnFunnels();
			spawntimer = 0;
			finished = false;
		}
		if (!islooped)
			ToggleWaypoint();
		if (_hp < 1800)
			phase = 2;

		FirstAttack(dt);
		
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

			SecondAttack(dt);
		if (_hp < 1000)
			TriggerFinal();

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

		break;
	}



}

void BConstruct::SetData(float scale)
{
	_spawnPos = Vec2(4000, 650)*scale;
	_destination = Vec2(1400, 600)*scale;
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
	if (timer - prevt > 0.07 && !finished)
	{
		prevt = timer;
		counter++;

		Vec2 pos = _eSprite->getPosition();
		
		Projectile* projectile = new Projectile();
		projectile->InitComplexBullet("Projectiles/enemy_bullet.png", Vec2(pos.x+i, pos.y-i*i), Vec2(-1, i*0.1),900,true);
		Projectile* projectile2 = new Projectile();
		projectile2->InitComplexBullet("Projectiles/enemy_bullet.png", Vec2(pos.x - i, pos.y - i*i), Vec2(-1, -i*0.1), 900,true);
		//Projectile* projectile3 = new Projectile();
		//projectile3->InitBasicBullet("Projectiles/enemy_bullet.png", -pos, 100, Vec2(-1, 0));
		if (counter > 8)
		{
			counter = 0;
			finished = true;
		}
		

	}


}
void BConstruct::UpdateHP()
{
	if (!IsDead()){
		float BossHealthScaleX = (_hp / MaxHp) * 200.F;
		BossHealthBarGreen->setScaleX(BossHealthScaleX);
		BossHealthNumber->setString(std::to_string(static_cast<int>(_hp)) + "/" + std::to_string(static_cast<int>(MaxHp)));
	}
	else
	{
		BossHealthBarGreen->removeFromParentAndCleanup(true);
		BossHealthBarRed->removeFromParentAndCleanup(true);
		BossHealthNumber->removeFromParentAndCleanup(true);
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
		projectile->InitComplexBullet("Projectiles/enemy_bullet.png", Vec2(pos.x-120, pos.y-120+i), Vec2(-2, -0.6+i*0.2).getNormalized(), 270, true,true);
		Projectile* projectile2 = new Projectile();
		projectile2->InitComplexBullet("Projectiles/enemy_bullet.png", Vec2(pos.x+120, pos.y-120+i), Vec2(-2, -0.6 + i*0.2).getNormalized(), 270, true,true);
		Projectile* projectile3 = new Projectile();
		projectile3->InitComplexBullet("Projectiles/enemy_bullet.png", Vec2(pos.x - 120+i, pos.y + 120), Vec2(-2, -0.6 + i*0.2).getNormalized(), 270, true,true);
		Projectile* projectile4 = new Projectile();
		projectile4->InitComplexBullet("Projectiles/enemy_bullet.png", Vec2(pos.x -120+ i, pos.y - 120), Vec2(-2, -0.6 + i*0.2).getNormalized(), 270, true,true);
	
		if (counter > 5)
			counter = 1;
	}
}

void BConstruct::TriggerFinal()
{
	islooped = true;
	//AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::CONSTRUCT_ACTIVEP2, true);
	_eSprite->stopAllActions();
	auto anim1 = Animate::create(AnimHandler::GetInstance()->getAnimAction(AnimHandler::CONSTRUCT_TPHASE));
	_eSprite->runAction(CCSequence::create(anim1, CallFunc::create(CC_CALLBACK_0(BConstruct::P3Loop, this)), NULL));
	phase = 3;
}

void BConstruct::P3Loop()
{
	if (islooped)
	{
		AnimHandler::GetInstance()->setAnimation(_eSprite, AnimHandler::CONSTRUCT_ACTIVEP2, true);
	}

	islooped = false;
	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Sprite* player = helloLayer->mainPlayer->GetSprite();
	auto moveTo = MoveTo::create(2, player->getPosition());
	_eSprite->runAction(CCSequence::create(moveTo,CallFunc::create(CC_CALLBACK_0(BConstruct::P3Loop, this)), NULL));
}