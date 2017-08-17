#include "explosion.h"
#include "HelloWorldScene.h"
#include "AnimationHandler.h"
Explosion::Explosion()
{

}

Explosion::~Explosion()
{

}

void Explosion::GenerateExplosion(Vec2 pos, EXPLODE_TYPE type)
{
	auto scene = Director::getInstance()->getRunningScene();
	auto layer = scene->getChildByTag(999);
	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	Node* SpriteNode = helloLayer->pwNode;
	switch (type)
	{
	case(EX_CLEAR):	// clear the screen
	{
		_eSprite = Sprite::create("shield.png");
		_eSprite->setScale(0.02);
		_eSprite->setPosition(pos);

		SpriteNode->addChild(_eSprite, -1);

		auto anim1 = Animate::create(AnimHandler::GetInstance()->getAnimAction(AnimHandler::EXPLOSION_CLEAR));
		auto scaleTo = ScaleTo::create(0.7f, 10.f);
		_eSprite->runAction(CCSequence::create(anim1, CallFunc::create(CC_CALLBACK_0(Explosion::SelfDelete, this)), NULL));
		_eSprite->runAction(scaleTo);
	}
		break;
	case(EX_SMALL):
		_eSprite = Sprite::create("shield.png");
		{
			_eSprite->setScale(1.7);
			_eSprite->setPosition(pos);
			SpriteNode->addChild(_eSprite, -1);

			auto anim2 = Animate::create(AnimHandler::GetInstance()->getAnimAction(AnimHandler::EXPLOSION));
			//auto scaleTo = ScaleTo::create(0.7f, 10.f);
			_eSprite->runAction(CCSequence::create(anim2, CallFunc::create(CC_CALLBACK_0(Explosion::SelfDelete, this)), NULL));
			//_eSprite->runAction(scaleTo);
		}
		break;


	}
}

void Explosion::ScreenExplode()
{

}

void Explosion::SelfDelete()
{
	this->_eSprite->removeFromParentAndCleanup(true);
	delete this;
}

