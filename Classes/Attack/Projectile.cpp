#include "Projectile.h"
#include "Scenes\HelloWorldScene.h"



Sprite* Projectile::InitBasicBullet(string BulletImg, Vec2 SpawnPosition,float BulletSpeed,float LifeTime,bool isEnemy)
{
	Sprite* Projectile = Sprite::create(BulletImg);

	ProjectileSpeed = BulletSpeed;
    Projectile->setPosition(SpawnPosition.x - Projectile->getContentSize().width, SpawnPosition.y - Projectile->getContentSize().height);
	Projectile->setScaleY(2.0f);
	Projectile->setScaleX(2.0f);
	//Projectile->setAnchorPoint(Vec2::ZERO);
	auto physicsBody = PhysicsBody::createBox(
		Size(Projectile->getContentSize().width, Projectile->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(2);
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(4);

	physicsBody->setVelocity(Vec2(1.f, 0.f) * ProjectileSpeed);
	physicsBody->setTag(1);
	Projectile->addComponent(physicsBody);

	auto moveEvent = MoveBy::create(LifeTime, Vec2(0.f, 0.f) );
	Projectile->runAction(moveEvent);
	//auto moveEvent = MoveBy::create(LifeTime, Vec2(5.f, 0.f) * ProjectileSpeed);
	//Projectile->runAction(moveEvent);


	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(Projectile, -1);

	return Projectile;
}

Sprite* Projectile::InitBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed, Vec2 direction, bool isEnemy)
{
	float lifetime = 5;
	Sprite* Projectile = Sprite::create(BulletImg);
	//Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
	Projectile->setScale(0.1);
	Projectile->setPosition(SpawnPosition.x, SpawnPosition.y);
	ProjectileSpeed = BulletSpeed;
	auto physicsBody = PhysicsBody::createBox(
		Size(Projectile->getContentSize().width, Projectile->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(8);
	physicsBody->setCollisionBitmask(33);
	physicsBody->setContactTestBitmask(33);
	physicsBody->setTag(3);
	physicsBody->setVelocity(direction * ProjectileSpeed);
	physicsBody->setGravityEnable(false);
	Projectile->addComponent(physicsBody);
	auto moveEvent = MoveBy::create(lifetime, Vec2(0.f, 0.f));
	Projectile->runAction(moveEvent);
	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(Projectile, -1);

	return Projectile;
}

//Sprite*  Projectile::getProjectileSprite()
//{
//	return ProjectileSprite;
//}
//void  Projectile::setProjectileSprite(Sprite* ProjectileSprite)
//{
//	this->ProjectileSprite = ProjectileSprite;
//}
Sprite*  Projectile::InitLaserBullet(string LaserImg, Vec2 SpawnPosition)
{
	Sprite* Projectile = Sprite::create(LaserImg);
	Projectile->setAnchorPoint(Vec2::ZERO);
    Projectile->setPosition(SpawnPosition.x - Projectile->getContentSize().width, SpawnPosition.y - Projectile->getContentSize().height);
	Projectile->setScaleY(1.f);
	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Projectile->setScaleX(helloLayer->playingSize.width-Projectile->getPosition().x);

	auto physicsBody = PhysicsBody::createBox(
		Size(Projectile->getContentSize().width, Projectile->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(128);
	physicsBody->setCollisionBitmask(4);
	physicsBody->setContactTestBitmask(4);
	physicsBody->setTag(7);
	//physicsBody->life
	//physicsBody->setVelocity(direction * ProjectileSpeed);
	physicsBody->setGravityEnable(false);
	Projectile->addComponent(physicsBody);

	
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(Projectile, -1);
	return Projectile;
}