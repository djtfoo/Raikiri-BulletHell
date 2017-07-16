#include "Powerup.h"
#include "Scenes\HelloWorldScene.h"
#include "AnimationHandler.h"

#include "Attack/Shield.h"

std::vector<Powerup*> Powerup::powerupsList;
bool Powerup::toSpawnPowerup = false;
Vec2 Powerup::spawnPosition = Vec2(300.f, 300.f);
bool Powerup::toDestroy = false;

void Powerup::InitPowerup(POWERUP_TYPE type, const Vec2& SpawnPosition)
{
	//string spriteDirectory = "Powerups/";

    powerupType = type;

	powerupSprite = Sprite::create();
	switch (type)
	{
	case POWERUP_LIVES:
		AnimHandler::GetInstance()->setAnimation(powerupSprite, AnimHandler::POWERUP_LIVES, true);
		break;

	case POWERUP_BULLETS:
		AnimHandler::GetInstance()->setAnimation(powerupSprite, AnimHandler::POWERUP_BULLET, true);
		break;

	case POWERUP_MISSILE:
		AnimHandler::GetInstance()->setAnimation(powerupSprite, AnimHandler::POWERUP_MISSILE, true);
		break;

	case POWERUP_SHIELD:
		AnimHandler::GetInstance()->setAnimation(powerupSprite, AnimHandler::POWERUP_SHIELD, true);
		break;

	case POWERUP_LASER:
		AnimHandler::GetInstance()->setAnimation(powerupSprite, AnimHandler::POWERUP_LASER, true);
		break;

	default:
		AnimHandler::GetInstance()->setAnimation(powerupSprite, AnimHandler::POWERUP_BULLET, true);
		break;
	}

	Vec2 spriteSize = Vec2(140.f, 140.f);

	powerupSprite->setScale(0.5);
	powerupSprite->setPosition(SpawnPosition.x + 0.5f * spriteSize.x, SpawnPosition.y + 0.5f * spriteSize.y);

	auto physicsBody = PhysicsBody::createBox(
		Size(spriteSize.x, spriteSize.y),
		PhysicsMaterial(0.f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(16);
	physicsBody->setContactTestBitmask(1);
	physicsBody->setCollisionBitmask(1);
	physicsBody->setTag(4);

	physicsBody->setGravityEnable(false);
	powerupSprite->addComponent(physicsBody);

	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(powerupSprite, -1);

    // set to "follow background" & move towards end of screen
    /// speed = dist / time
    /// time = dist / speed
    /// speed is const
    /// dist is x-dist away from edge of screen (aka x-coord)
    auto moveEvent = MoveTo::create(powerupSprite->getPosition().x / 100.f, Vec2(0.f, powerupSprite->getPosition().y));

    auto callbackFunc = CallFunc::create([this]() {
        DestroySelf();
    });
    auto seq = Sequence::create(moveEvent, callbackFunc, nullptr);
    powerupSprite->runAction(seq);
}

Sprite* Powerup::GetPowerupSprite()
{
	return powerupSprite;
}

Powerup::POWERUP_TYPE Powerup::GetPowerupType()
{
	return powerupType;
}

// function to call that checks whether a powerup should be spawned
bool Powerup::CheckSpawnPowerup()
{
	// percentage chance of drop: 30%
	int chance = cocos2d::RandomHelper::random_int(1, 10);
	if (chance < 5)
		return true;

	return false;
}

void Powerup::RandomSpawnPowerup()
{
	int toSpawn = cocos2d::RandomHelper::random_int(0, (int)POWERUPS_TOTAL - 1);

	Powerup* newPowerup = new Powerup();
	//newPowerup->InitPowerup(static_cast<POWERUP_TYPE>(toSpawn), spawnPosition);
    newPowerup->InitPowerup(POWERUP_SHIELD, spawnPosition);

	powerupsList.push_back(newPowerup);
}

void Powerup::FindAndBeginPickup(Node* node, const Vec2& pos)
{
	for (std::vector<Powerup*>::iterator it = powerupsList.begin(); it != powerupsList.end(); ++it)
	{
		Powerup* powerup = *it;
		if (powerup->powerupSprite == node)
		{
			// begin pickup
			powerup->BeginPickup(pos);
			break;
		}
	}
}

void Powerup::BeginPickup(const Vec2& pos)
{
	auto moveEvent = MoveTo::create(0.3f, pos);

	auto callbackFunc = CallFunc::create([this]() {
		ApplyPowerupEffect();
	});
	auto seq = Sequence::create(moveEvent, callbackFunc, nullptr);
	powerupSprite->runAction(seq);
}

void Powerup::DestroySelf()
{
    toBeDestroyed = true;	// personal variable
    toDestroy = true;	// static variable
}

// apply effect and play SFX
void Powerup::ApplyPowerupEffect()
{
	// apply power-up effect here
	switch (powerupType)
	{
	case POWERUP_LIVES:
		break;

	case POWERUP_BULLETS:
		break;

	case POWERUP_MISSILE:
		break;

	case POWERUP_SHIELD:
    {
        Shield::SetToSpawnShield(true);
        auto scene = Director::getInstance()->getRunningScene();
        auto layer = scene->getChildByTag(999);
        HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
        Shield::SetSpawnUser(helloLayer->mainPlayer->GetSprite(), true);
    }
		break;

	case POWERUP_LASER:
		break;

	default:
		break;
	}

	toBeDestroyed = true;	// personal variable
	toDestroy = true;	// static variable
}

bool Powerup::IsToDestroy()
{
	return toDestroy;
}

void Powerup::DestroyPickedups()
{
	for (std::vector<Powerup*>::iterator it = powerupsList.begin(); it != powerupsList.end(); ++it)
	{
		Powerup* powerup = *it;
		if (powerup->toBeDestroyed == true)
		{
			// delete Powerup sprite
			Node* sprite = powerup->powerupSprite;
			sprite->removeFromParentAndCleanup(true);

			// delete internal Powerup object
			delete powerup;

			// remove from list
			powerupsList.erase(it);
			toDestroy = false;

			break;
		}
	}
}