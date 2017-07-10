#include "Powerup.h"
#include "Scenes\HelloWorldScene.h"

std::map<int, Powerup*> Powerup::powerupsList;
int Powerup::powerupSpawnCount = 0;
bool Powerup::toSpawnPowerup = false;
Vec2 Powerup::spawnPosition = Vec2(300.f, 300.f);

void Powerup::InitPowerup(POWERUP_TYPE type, Vec2 SpawnPosition)
{
	string spriteDirectory = "Powerups/";
	switch (type)
	{
	case POWERUP_LIVES:
		spriteDirectory += "powerup_lives.png";
		break;

	case POWERUP_BULLETS:
		spriteDirectory += "powerup_bullets.png";
		break;

	case POWERUP_MISSILE:
		spriteDirectory += "powerup_missile.png";
		break;

	case POWERUP_SHIELD:
		spriteDirectory += "powerup_shield.png";
		break;

	default:
		spriteDirectory += "powerup_bullets.png";
		break;
	}

	powerupSprite = Sprite::create(spriteDirectory);

	powerupSprite->setPosition(SpawnPosition.x + powerupSprite->getContentSize().width, SpawnPosition.y + powerupSprite->getContentSize().height);

	auto physicsBody = PhysicsBody::createBox(
		Size(powerupSprite->getContentSize().width, powerupSprite->getContentSize().height),
		PhysicsMaterial(0.f, 0.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setContactTestBitmask(1);
	physicsBody->setTag(4);

	//physicsBody->setVelocity(Vec2(100.f, 0.f));
	physicsBody->setGravityEnable(false);
	powerupSprite->addComponent(physicsBody);

	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(powerupSprite, -1);
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
	if (chance < 10)
		return true;

	return false;
}

void Powerup::RandomSpawnPowerup()
{
	int toSpawn = cocos2d::RandomHelper::random_int(0, (int)POWERUPS_TOTAL - 1);
	
	Powerup* newPowerup = new Powerup();
	newPowerup->InitPowerup(static_cast<POWERUP_TYPE>(toSpawn), spawnPosition);
	powerupsList.insert(std::pair<int, Powerup*>(powerupSpawnCount++, newPowerup));
}

// apply effect and play SFX
void Powerup::Pickup()
{

}