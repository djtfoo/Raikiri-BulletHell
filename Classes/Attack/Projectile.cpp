#include "Projectile.h"
#include "Scenes\HelloWorldScene.h"



Sprite* Projectile::InitBasicBullet(string BulletImg, Vec2 SpawnPosition,float BulletSpeed,float LifeTime)
{
	Sprite* Projectile = Sprite::create(BulletImg);

	//Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
    Projectile->setPosition(SpawnPosition.x, SpawnPosition.y);

	ProjectileSpeed = BulletSpeed;
	auto moveEvent = MoveBy::create(LifeTime, Vec2(5.f, 0.f) * ProjectileSpeed);
	Projectile->runAction(moveEvent);

	ProjectileSpeed = BulletSpeed;
	Projectile->setAnchorPoint(Vec2::ZERO);
	auto physicsBody = PhysicsBody::createBox(
		Size(Projectile->getContentSize().width, Projectile->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(0x01);
	physicsBody->setCollisionBitmask(0x02);
	
	physicsBody->setVelocity(Vec2(1.f, 0.f) * ProjectileSpeed);
	physicsBody->setGravityEnable(false);
	Projectile->addComponent(physicsBody);
	



    Projectile->setPosition(SpawnPosition.x - Projectile->getContentSize().width, SpawnPosition.y - Projectile->getContentSize().height);
	Projectile->setScaleY(2.0f);
	Projectile->setScaleX(2.0f);
	
	//auto moveEvent = MoveBy::create(LifeTime, Vec2(5.f, 0.f) * ProjectileSpeed);
	//Projectile->runAction(moveEvent);


	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(Projectile, -1);
	return Projectile;

}

Sprite* Projectile::InitBasicBullet(string BulletImg, Vec2 SpawnPosition, float BulletSpeed,Vec2 direction)
{
	float lifetime = 5;
	Sprite* Projectile = Sprite::create(BulletImg);
	//Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
	Projectile->setScale(0.1);
	Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
	ProjectileSpeed = BulletSpeed;
	auto moveEvent = MoveBy::create(lifetime, direction * ProjectileSpeed*lifetime);
	Projectile->runAction(moveEvent);

	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(Projectile, -1);
	return Projectile;

}

Sprite*  Projectile::getProjectileSprite()
{
	return ProjectileSprite;
}
void  Projectile::setProjectileSprite(Sprite* ProjectileSprite)
{
	this->ProjectileSprite = ProjectileSprite;
}
Sprite*  Projectile::InitLaserBullet(string LaserImg, Vec2 SpawnPosition)
{
	Sprite* Projectile = Sprite::create(LaserImg);
	Projectile->setAnchorPoint(Vec2::ZERO);
    //Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
    //Projectile->setPosition(SpawnPosition.x, SpawnPosition.y);
    Projectile->setPosition(SpawnPosition.x - Projectile->getContentSize().width, SpawnPosition.y - Projectile->getContentSize().height);
	Projectile->setScaleX(0.f);
	Projectile->setScaleY(4.0f);


	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getProjectileNode();
	SpriteNode->addChild(Projectile, 1);
	return Projectile;
}