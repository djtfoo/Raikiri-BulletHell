#include "Projectile.h"
#include "Scenes\HelloWorldScene.h"



Sprite* Projectile::InitBasicBullet(string BulletImg, Vec2 SpawnPosition,float BulletSpeed,float LifeTime)
{
	Sprite* Projectile = Sprite::create(BulletImg);
	Projectile->setAnchorPoint(Vec2::ZERO);
	Projectile->setPosition(SpawnPosition.x,SpawnPosition.y);
	Projectile->setScaleY(8.0f);
	Projectile->setScaleX(8.0f);
	ProjectileSpeed = BulletSpeed;
	auto moveEvent = MoveBy::create(LifeTime, 1 * Vec2(1.f, 0.f) * ProjectileSpeed);
	Projectile->runAction(moveEvent);

	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(Projectile, 1);
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
	Projectile->setAnchorPoint(Vec2(0, 0));
	Projectile->setPosition(SpawnPosition.x, SpawnPosition.y);
	Projectile->setScaleX(0.f);
	Projectile->setScaleY(8.0f);


	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->getSpriteNode();
	SpriteNode->addChild(Projectile, 1);
	return Projectile;
}