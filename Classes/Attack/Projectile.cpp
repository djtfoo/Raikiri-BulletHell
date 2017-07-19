#include "Projectile.h"
#include "Scenes\HelloWorldScene.h"
#define COCOS2D_DEBUG 1
Sprite* Projectile::InitBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, float LifeTime, bool isEnemy)
{
    ProjectileSprite = Sprite::create(BulletImg);
	ProjectileSprite->setScale(0.8);
    ProjectileSpeed = BulletSpeed;
    ProjectileSprite->setPosition(SpawnPosition.x , SpawnPosition.y);

    //Projectile->setAnchorPoint(Vec2::ZERO);
    auto physicsBody = PhysicsBody::createBox(
        Size(ProjectileSprite->getContentSize().width, ProjectileSprite->getContentSize().height),
        PhysicsMaterial(10.f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask(2);
    physicsBody->setCollisionBitmask(4);
    physicsBody->setContactTestBitmask(4);
	physicsBody->setVelocity(Vec2(BulletSpeed, 0));
    //physicsBody->setVelocity(Vec2(1.f, 0.f) * ProjectileSpeed);
    physicsBody->setTag(1);
    ProjectileSprite->addComponent(physicsBody);

    // Get HelloWorld Scene layer
    auto scene = Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(999);
    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
    Node* SpriteNode = helloLayer->getSpriteNode();

    auto moveEvent = MoveTo::create((helloLayer->playingSize.width - ProjectileSprite->getPosition().x) / 200.f, Vec2(helloLayer->playingSize.width, ProjectileSprite->getPosition().y));

    auto callbackFunc = CallFunc::create([this]() {
        ProjectileSprite->removeFromParentAndCleanup(true);

        // delete this Projectile object
        delete this;
    });
    auto seq = Sequence::create(moveEvent, callbackFunc, nullptr);
    ProjectileSprite->runAction(seq);

    SpriteNode->addChild(ProjectileSprite, -1);

    return ProjectileSprite;
}
Sprite* Projectile::InitBasicBullet(string BulletImg, Vec2 SpawnPosition, Vec2 direction, float BulletSpeed,  bool isEnemy, float lifetime)
{
    ProjectileSprite = Sprite::create(BulletImg);
    //Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
    //CCLOG("Position : 4.",  Projectile->getContentSize().width);
    ProjectileSprite->setPosition(SpawnPosition.x - (ProjectileSprite->getContentSize().width*0.3), SpawnPosition.y - (ProjectileSprite->getContentSize().height*0.2));
    ProjectileSpeed = BulletSpeed;
    auto physicsBody = PhysicsBody::createBox(
        Size(0.5f * ProjectileSprite->getContentSize().width, 0.5f * ProjectileSprite->getContentSize().height),
        PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask(8);
    physicsBody->setCollisionBitmask(33);
    physicsBody->setContactTestBitmask(33);
    physicsBody->setTag(3);
    //physicsBody->setVelocity(direction * ProjectileSpeed);
    physicsBody->setGravityEnable(false);
    ProjectileSprite->addComponent(physicsBody);
    
    // Get HelloWorld Scene layer
    auto scene = Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(999);
    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
    Node* SpriteNode = helloLayer->getSpriteNode();

    auto moveEvent = MoveBy::create(lifetime, direction * ProjectileSpeed);

    auto callbackFunc = CallFunc::create([this]() {
        ProjectileSprite->removeFromParentAndCleanup(true);

        // delete this Projectile object
        delete this;
    });
    auto seq = Sequence::create(moveEvent, callbackFunc, nullptr);
    ProjectileSprite->runAction(seq);

    SpriteNode->addChild(ProjectileSprite, -1);

    return ProjectileSprite;
}
Sprite* Projectile::InitComplexBullet(string BulletImg, Vec2 SpawnPosition, Vec2 vel, float BulletSpeed,  bool isEnemy,bool gravity,float lifetime)
{
	ProjectileSprite = Sprite::create(BulletImg);
	//Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
	//CCLOG("Position : 4.",  Projectile->getContentSize().width);
	ProjectileSprite->setPosition(SpawnPosition.x - (ProjectileSprite->getContentSize().width*0.3), SpawnPosition.y - (ProjectileSprite->getContentSize().height*0.2));
	ProjectileSpeed = BulletSpeed;
	auto physicsBody = PhysicsBody::createBox(
		Size(0.5f * ProjectileSprite->getContentSize().width, 0.5f * ProjectileSprite->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(8);
	physicsBody->setCollisionBitmask(33);
	physicsBody->setContactTestBitmask(33);
	physicsBody->setTag(3);
	physicsBody->setVelocity(vel * ProjectileSpeed);
	physicsBody->setGravityEnable(gravity);
	ProjectileSprite->addComponent(physicsBody);

	// Get HelloWorld Scene layer
	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();

	
	auto callbackFunc = CallFunc::create([this]() {
		ProjectileSprite->removeFromParentAndCleanup(true);

		// delete this Projectile object
		delete this;
	});
	auto seq = Sequence::create(DelayTime::create(lifetime), callbackFunc, nullptr);
	ProjectileSprite->runAction(seq);

	SpriteNode->addChild(ProjectileSprite, -1);

	return ProjectileSprite;
}
//Sprite*  Projectile::getProjectileSprite()
//{
//	return ProjectileSprite;
//}
//void  Projectile::setProjectileSprite(Sprite* ProjectileSprite)
//{
//	this->ProjectileSprite = ProjectileSprite;
//}
Sprite* Projectile::InitLaserBullet(string LaserImg, Vec2 SpawnPosition)
{
    Sprite* Projectile = Sprite::create(LaserImg);
    Projectile->setAnchorPoint(Vec2::ZERO);
    Projectile->setPosition(SpawnPosition.x - Projectile->getContentSize().width, SpawnPosition.y - Projectile->getContentSize().height);
    Projectile->setScaleY(1.f);
    auto scene = Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(999);
    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
    Projectile->setScaleX(helloLayer->playingSize.width /*- Projectile->getPosition().x*/);
   
    auto physicsBody = PhysicsBody::createBox(
        //Size((Projectile->getScaleX()/2)-Projectile->getPosition().x, Projectile->getContentSize().height),
        Size(1, Projectile->getContentSize().height),
        PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(false);
    physicsBody->setCategoryBitmask(128);
    physicsBody->setCollisionBitmask(4);
    physicsBody->setContactTestBitmask(4);
    physicsBody->setTag(7);
    physicsBody->setGravityEnable(false);
    Projectile->addComponent(physicsBody);


    Node* SpriteNode = helloLayer->getSpriteNode();
    SpriteNode->addChild(Projectile, -1);
    return Projectile;
}