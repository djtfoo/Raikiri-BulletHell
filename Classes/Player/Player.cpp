#include "Player.h"
#include "Scenes/HelloWorldScene.h"
#include "AnimationHandler.h"
#include "Audio/AudioManager.h"

void Player::Init(const char* imgSource, const char* playerName, float X, float Y)
{
	//remove imagesource for now
	mainSprite = Sprite::create();
	AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_SPAWN, false);
	mainSprite->setScale(0.6);
	mainSprite->setAnchorPoint(Vec2::ZERO);
	mainSprite->setPosition(X, Y);
	mainSprite->setName(playerName);
    auto spawnpos = MoveTo::create(1, Vec2(150, 100));
    mainSprite->runAction(spawnpos);
	fSpeed = 200.f;

	//AnimatePlayer(KEY_DOWN);
	//StopAnimation();


	// shader stuff
	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);

	charEffect = new GLProgram();
	charEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	AnimHandler::GetInstance()->Init();
	charEffect->link();
	charEffect->updateUniforms();

	this->intDirX = 0;
	this->intDirY = 0;

	lives = 1;
	score = 200;
	AttackSystems = new Attack();
}
int Player::getScore()
{
	return score;
}
void Player::setScore(int score)
{
	this->score = score;
}
void Player::Update(float dt)
{
	if (intDirX != 0) {
		auto moveEvent = MoveBy::create(0.f, intDirX * Vec2(1.f, 0.f) * fSpeed * dt);
		mainSprite->runAction(moveEvent);
	}
	if (intDirY != 0) {
		auto moveEvent = MoveBy::create(0.f, intDirY * Vec2(0.f, 1.f) * fSpeed * dt);
		mainSprite->runAction(moveEvent);
	}

	if (intDirY == 0 && intDirX == 0)
	{
		//StopAnimation();
	}
    AttackSystems->LaserUpdate(dt, 0.5f,
        mainSprite->getPosition() + Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f));
    //    mainSprite->getPosition() + (Vec2(mainSprite->getScaleX(),0) * 50));
	/*GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(charEffect);
	mainSprite->setGLProgram(charEffect);
	mainSprite->setGLProgramState(state);
	state->setUniformVec2("loc", mLoc);*/
}

void Player::AnimatePlayer(KEYCODE key)
{
	mainSprite->stopAllActions();
	//AnimHandler::getInstance()->Init();
	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);

	switch (key)
	{
	case KEY_RIGHT:
		//animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);

		break;

	case KEY_LEFT:
		//animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_BACK, true);
		break;

	case KEY_UP:
		//animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
		break;

	case KEY_DOWN:
		//animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
		//animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
		break;
	}

	// create the animation out of the frames
	//Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	//Animate* animateIdle = Animate::create(animation);
	//AnimHandler::getInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
	// run it and repeat it forever
	//mainSprite->runAction(RepeatForever::create(animateIdle));
}
void Player::FireBasicBullet()
{
	AttackSystems->FireBasicBullet("Projectiles/Bullet.png",
        mainSprite->getPosition() + Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f),
        //mainSprite->getPosition()+Vec2(mainSprite->getScaleX()*50,0),
        10000,25);
    AudioManager::GetInstance()->PlaySoundEffect("Bullet");
}
void Player::FireLaser()
{
	AttackSystems->FireLaserBullet("Projectiles/Laser.png",
        mainSprite->getPosition() + Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f),
        //mainSprite->getPosition() + Vec2(mainSprite->getScaleX() * 50, 0),
        10);
    AudioManager::GetInstance()->PlaySoundEffect("Laser");
}
void Player::StopFiringLaser()
{
	AttackSystems->StopFiringLaser(5000, 25);
}
void Player::StopAnimation()
{
	//mainSprite->stopAllActions();

	//Vector<SpriteFrame*> animFrames;
	//animFrames.reserve(4);

	// insert idle animation here
	//animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
	//animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
	//animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
	//animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));

	// create the animation out of the frames
	//Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	//Animate* animateIdle = Animate::create(animation);

	//AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);

	// run it and repeat it forever
	//mainSprite->runAction(RepeatForever::create(animateIdle));
}

void Player::SetMoveCharX(int dirX)
{
	intDirX = dirX;
    if (dirX == -1)
        AnimatePlayer(KEY_LEFT);
    else if (dirX == 1)
        AnimatePlayer(KEY_RIGHT);

}

void Player::SetMoveCharY(int dirY)
{
	intDirY = dirY;
    if (dirY == -1)
        AnimatePlayer(KEY_DOWN);
    else if (dirY == 1)
        AnimatePlayer(KEY_UP);
}
int Player::getLives()
{
	return lives;
}
void Player::setLives(int lives)
{
	this->lives = lives;
}
void Player::MoveCharByCoord(float X, float Y)
{
	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);

	animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));

	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateIdle = Animate::create(animation);

	// run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animateIdle));

	float diffX = X - mainSprite->getPosition().x;
	float diffY = Y - mainSprite->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	//Vec2 destinationPos = Vec2(X, Y);
	auto moveEvent = MoveBy::create(vec.length() * 0.01f, vec);
	//auto moveEvent = MoveTo::create(destinationPos.length() / fSpeed, destinationPos);

	auto callbackStop = CallFunc::create([]() {
		//mainSprite->stopAllActions();
		auto scene = Director::getInstance()->getRunningScene();
		auto layer = scene->getChildByTag(999);
		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
		//if (helloLayer != NULL)
		//	helloLayer->GetPlayer()->StopAnimation();
	});
	auto seq = Sequence::create(moveEvent, callbackStop, nullptr);
	mainSprite->runAction(seq);
}