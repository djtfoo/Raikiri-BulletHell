#include "Shield.h"
#include "../Scenes/HelloWorldScene.h"

Shield* Shield::playerShield = NULL;
std::map<Entity*, Shield*> Shield::entityShieldsList;

bool Shield::toSpawnShield = false;
Sprite* Shield::spawnUserSprite = NULL;
bool Shield::isSpawnUserPlayer = false;

bool Shield::toDestroy = false;
bool Shield::isToDestroyPlayer = false;

void Shield::InitShield(Sprite* userSprite)
{
    shieldSprite = Sprite::create("shield.png");
    
    spriteSize = userSprite->getContentSize();
    spriteSize = Vec2(0.4f * spriteSize.x, 0.4f * spriteSize.y);

    const Vec2 imageSize = shieldSprite->getContentSize();
    shieldSprite->setScale(spriteSize.x / imageSize.x, spriteSize.y / imageSize.y);

    this->userSprite = userSprite;
    shieldSprite->setPosition(userSprite->getPosition().x, userSprite->getPosition().y);

    auto physicsBody = PhysicsBody::createBox(
        Size(spriteSize.x, spriteSize.y),
        PhysicsMaterial(0.f, 0.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(32);
    physicsBody->setContactTestBitmask(8);
	physicsBody->setCollisionBitmask(8);
    if (isSpawnUserPlayer)
        physicsBody->setTag(5); // Player Shield
    else
        physicsBody->setTag(6); // Entity Shield

    physicsBody->setGravityEnable(false);
    shieldSprite->addComponent(physicsBody);

    auto scene = Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(999);
    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
    Node* SpriteNode = helloLayer->getSpriteNode();
    SpriteNode->addChild(shieldSprite, -1);

    toBeDestroyed = false;
}

void Shield::UpdatePosition()
{
    shieldSprite->setPosition(userSprite->getPosition().x, userSprite->getPosition().y);
}

// static function: spawn a shield
void Shield::SpawnShield()
{
    if (isSpawnUserPlayer)
    {
        if (playerShield == NULL)
        {
            // create Shield
            playerShield = new Shield();
            playerShield->InitShield(Shield::spawnUserSprite);
        }
    }
    else
    {
        auto scene = Director::getInstance()->getRunningScene();
        auto layer = scene->getChildByTag(999);
        HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
        
        Entity* entity = helloLayer->waveSpawner->GetEntity(Shield::spawnUserSprite);
        if (entityShieldsList.find(entity) == entityShieldsList.end())  // this Entity does not have Shield yet
        {
            // create Shield
            Shield* newShield = new Shield();
            newShield->InitShield(Shield::spawnUserSprite);
            entityShieldsList.insert(std::pair<Entity*, Shield*>(entity, newShield));
        }
    }
}

void Shield::SetDestroyPlayerShield()
{
    playerShield->toBeDestroyed = true;
    isToDestroyPlayer = true;
    toDestroy = true;
}

void Shield::SetDestroyEntityShield(Entity* entity)
{
    std::map<Entity*, Shield*>::iterator it = entityShieldsList.find(entity);
    if (it != entityShieldsList.end())
    {
        isToDestroyPlayer = false;
        it->second->toBeDestroyed = true;
        toDestroy = true;
    }
}

// static functions handling destruction of picked up powerups
void Shield::DestroyShield()
{
    if (isToDestroyPlayer)
    {
        // delete Shield sprite
        Node* sprite = playerShield->shieldSprite;
        sprite->removeFromParentAndCleanup(true);

        // delete internal Shield object
        delete playerShield;
        playerShield = NULL;

        toDestroy = false;
    }

    else
    {
        for (std::map<Entity*, Shield*>::iterator it = entityShieldsList.begin(); it != entityShieldsList.end(); ++it)
        {
            Shield* shield = it->second;
            if (shield->toBeDestroyed == true)
            {
                // delete Shield sprite
                Node* sprite = shield->shieldSprite;
                sprite->removeFromParentAndCleanup(true);

                // delete internal Shield object
                delete shield;

                // remove from list
                entityShieldsList.erase(it);
                toDestroy = false;

                break;
            }
        }
    }
}

bool Shield::IsToDestroy()
{
    return toDestroy;
}