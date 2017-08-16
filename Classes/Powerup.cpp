#include "Powerup.h"
#include "HelloWorldScene.h"
#include "AnimationHandler.h"
#include "AudioManager.h"

#include "Shield.h"

std::vector<Powerup*> Powerup::activePowerupsList;
std::vector<Powerup*> Powerup::inactivePowerupsList;
bool Powerup::toSpawnPowerup = false;
Vec2 Powerup::spawnPosition = Vec2(300.f, 300.f);
bool Powerup::toDestroy = false;

void Powerup::PopulatePowerupPool()
{
    // create 10 inactive Powerups
    for (int i = 0; i < 10; ++i)
    {
        CreateInactivePowerup();
    }
}

void Powerup::ClearPowerupPool()
{
    activePowerupsList.clear();
    inactivePowerupsList.clear();
}

void Powerup::CreateInactivePowerup()
{
    Powerup* newPowerup = new Powerup();

    newPowerup->powerupSprite = Sprite::create();

    Vec2 spriteSize = Vec2(140.f, 140.f);

    newPowerup->powerupSprite->setScale(0.5);
    newPowerup->powerupSprite->setVisible(false);

    auto physicsBody = PhysicsBody::createBox(
        Size(spriteSize.x, spriteSize.y),
        PhysicsMaterial(0.f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(16);
    physicsBody->setContactTestBitmask(1);
    physicsBody->setCollisionBitmask(1);
    physicsBody->setTag(4);

    physicsBody->setGravityEnable(false);
    newPowerup->powerupSprite->addComponent(physicsBody);

    physicsBody->setEnabled(false);

    auto scene = Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(999);
    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
    Node* pwNode = helloLayer->pwNode;
    pwNode->addChild(newPowerup->powerupSprite, -1);
	//spriteNode->addChild(newPowerup->powerupSprite, -1);
    inactivePowerupsList.push_back(newPowerup);
}

void Powerup::InitPowerup(POWERUP_TYPE type, const Vec2& SpawnPosition)
{
	//string spriteDirectory = "Powerups/";

    powerupType = type;
    Vec2 spriteSize = Vec2(140.f, 140.f);

    powerupSprite->setPosition(SpawnPosition.x + 0.5f * spriteSize.x, SpawnPosition.y + 0.5f * spriteSize.y);
    powerupSprite->setVisible(true);

    powerupSprite->getPhysicsBody()->setEnabled(true);

    powerupSprite->stopAllActions();

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
	// percentage chance of drop: 40%
	int chance = cocos2d::RandomHelper::random_int(1, 10);
	if (chance < 10)
		return true;

	return false;
}

void Powerup::RandomSpawnPowerup()
{
    // if inactive list is empty, populate it first
    if (inactivePowerupsList.empty())
    {
        PopulatePowerupPool();
    }

    // fetch a Powerup from inactive list
    Powerup* powerup = inactivePowerupsList[0];
    inactivePowerupsList.erase(inactivePowerupsList.begin());

    // set powerup
    int toSpawn = cocos2d::RandomHelper::random_int(0, (int)POWERUPS_TOTAL - 1);

    powerup->InitPowerup(static_cast<POWERUP_TYPE>(toSpawn), spawnPosition);
   // powerup->InitPowerup(POWERUP_BULLETS, spawnPosition);

    // move to active powerups list
   activePowerupsList.push_back(powerup);
}

void Powerup::FindAndBeginPickup(Node* node, const Vec2& pos)
{
	for (std::vector<Powerup*>::iterator it = activePowerupsList.begin(); it != activePowerupsList.end(); ++it)
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

void Powerup::Update()
{
    powerupSprite->getPhysicsBody()->onAdd();
}

void Powerup::PowerupsUpdate()
{
    for (Powerup* powerup : activePowerupsList)
    {
        powerup->Update();
    }
}

// apply effect and play SFX
void Powerup::ApplyPowerupEffect()
{
	// apply power-up effect here
	switch (powerupType)
	{
    case POWERUP_LIVES:
    {
        auto scene = Director::getInstance()->getRunningScene();
        auto layer = scene->getChildByTag(999);
        HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);

        int newLives = helloLayer->mainPlayer->getLives() + 1;
        helloLayer->mainPlayer->setLives(newLives);

        // Update GUI
        helloLayer->GetGUI()->UpdateLivesLabel(std::to_string(newLives).c_str());
    }
		break;

	case POWERUP_BULLETS:
    {
        auto scene = Director::getInstance()->getRunningScene();
        auto layer = scene->getChildByTag(999);
        HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
        helloLayer->mainPlayer->Upgrade();
    }
		break;

	case POWERUP_MISSILE:
    {
		auto scene = Director::getInstance()->getRunningScene();
		auto layer = scene->getChildByTag(999);
		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
		helloLayer->mainPlayer->UpgradeMissiles();
    }
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
    {
        auto scene = Director::getInstance()->getRunningScene();
        auto layer = scene->getChildByTag(999);
        HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
        helloLayer->mainPlayer->GetAttackSystems()->SetLaserMode(true);
    }
		break;

	default:
		break;
	}
    
    AudioManager::GetInstance()->PlaySoundEffect("Powerup", false);

	toBeDestroyed = true;	// personal variable
	toDestroy = true;	// static variable
}

bool Powerup::IsToDestroy()
{
	return toDestroy;
}

void Powerup::DestroyPickedups()
{
	for (std::vector<Powerup*>::iterator it = activePowerupsList.begin(); it != activePowerupsList.end(); ++it)
	{
		Powerup* powerup = *it;
		if (powerup->toBeDestroyed == true)
		{
			/// delete Powerup sprite
			//Node* sprite = powerup->powerupSprite;
			//sprite->removeFromParentAndCleanup(true);

			/// delete internal Powerup object
			//delete powerup;

            // set sprite to inactive
            powerup->powerupSprite->setVisible(false);
            powerup->powerupSprite->getPhysicsBody()->setEnabled(false);

			// remove from list
            activePowerupsList.erase(it);

            // return it to inactive list
            inactivePowerupsList.push_back(powerup);
            powerup->toBeDestroyed = false;

			toDestroy = false;

			break;
		}
	}
}