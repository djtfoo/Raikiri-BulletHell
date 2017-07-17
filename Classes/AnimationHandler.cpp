#include "AnimationHandler.h"

USING_NS_CC;

//setting s_instance to nothing to trigger new animhandler in getinstance
//AnimHandler *AnimHandler::s_instance = 0;


AnimHandler::~AnimHandler()
{

}

void AnimHandler::Init()
{
	//add sprite sheets to the cache
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ship_idle.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ship_spawn.plist");
	animSpeed = 30;
	addAnimation("ship.plist", "ship_idle%04d.png", 15, SHIP_IDLE);
	addAnimation("ship_spawn.plist", "ship_spawn%04d.png", 50, SHIP_SPAWN);
	addAnimation("ship.plist", "ship_back%04d.png", 15, SHIP_BACK);

	addAnimation("capule.plist", "capule_spawn%04d.png", 40, CAPULE_SPAWN);
	addAnimation("capule.plist", "capule_active%04d.png", 15, CAPULE_ACTIVE);

	addAnimation("platonic.plist", "platonic_spawn%04d.png", 30, PLATONIC_SPAWN);
	addAnimation("platonic.plist", "platonic_active%04d.png", 30, PLATONIC_ACTIVE);

	addAnimation("constructfunnel.plist", "constructfunnel_spawn%04d.png", 50, CONSTRUCTFUNNEL_SPAWN);
	addAnimation("constructfunnel.plist", "constructfunnel_active%04d.png", 30, CONSTRUCTFUNNEL_ACTIVE);
	addAnimation("construct_active.plist", "construct_active%04d.png", 30, CONSTRUCT_ACTIVE);
	addAnimation("construct_activep2.plist", "construct_activep2_%04d.png", 30, CONSTRUCT_ACTIVEP2);
	addAnimation("construct_tphase.plist", "construct_tphase2_%04d.png", 30, CONSTRUCT_TPHASE);

	addAnimation("powerup.plist", "powerup_bullet%04d.png", 15, POWERUP_BULLET);
	addAnimation("powerup.plist", "powerup_laser%04d.png", 15, POWERUP_LASER);
	addAnimation("powerup.plist", "powerup_lives%04d.png", 15, POWERUP_LIVES);
	addAnimation("powerup.plist", "powerup_missile%04d.png", 15, POWERUP_MISSILE);
	addAnimation("powerup.plist", "powerup_shield%04d.png", 15, POWERUP_SHIELD);
}

void AnimHandler::Update(float dt)
{

}

void AnimHandler::addAnimation(const char* plist, const char* format, int framecount, ANIMATION_TYPE  name)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);

	Vector<SpriteFrame*> frames = getAnimation(format, framecount);
	auto animation = Animation::createWithSpriteFrames(frames, 1.0f / animSpeed);//Xseconds/Yframes (Yframes per second)

	animList[name] = animation;
}

void AnimHandler::setAnimation(Sprite* sprite, ANIMATION_TYPE  name, bool loop)
{
	if (loop)
	sprite->runAction(RepeatForever::create(Animate::create(animList[name])));
	else
		sprite->runAction(Animate::create(animList[name]));

    sprite->getPhysicsBody()->onAdd();
}

void AnimHandler::setCCAnimation(Sprite* sprite, ANIMATION_TYPE  name,CallFunc* callback)
{
	sprite->runAction(CCSequence::create(Animate::create(animList[name]), callback, NULL));

    sprite->getPhysicsBody()->onAdd();
}

Animation* AnimHandler::getAnimAction(ANIMATION_TYPE name)
{
		return animList[name];
}

Vector<cocos2d::SpriteFrame*> AnimHandler::getAnimation(const char *format, int count)
{
	auto spritecache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 0; i <= count; i++)
	{
		sprintf(str, format, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	return animFrames;
}

void AnimHandler::setAnimframe(Sprite* sprite, ANIMATION_TYPE  name)
{
    //sprite = Sprite::create(animList[name]->createWithSpriteFrames)
}

