#include "Player.h"
#include "Scenes/HelloWorldScene.h"

void Player::Init(const char* imgSource, const char* playerName, float X, float Y)
{
	mainSprite = Sprite::create(imgSource);
	mainSprite->setAnchorPoint(Vec2::ZERO);
	mainSprite->setPosition(X, Y);
	mainSprite->setName(playerName);
	
	fSpeed = 200.f;

	AnimatePlayer(KEY_DOWN);
	StopAnimation();


	// shader stuff
	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);

	charEffect = new GLProgram();
	charEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/CharEffect.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

	charEffect->link();
	charEffect->updateUniforms();

	this->intDirX = 0;
	this->intDirY = 0;


	AttackSystems = new Attack();
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
		StopAnimation();
	}
	AttackSystems->LaserUpdate(dt, 0.1f, mainSprite->getPosition() );
	/*GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(charEffect);
	mainSprite->setGLProgram(charEffect);
	mainSprite->setGLProgramState(state);
	state->setUniformVec2("loc", mLoc);*/
}

void Player::AnimatePlayer(KEYCODE key)
{
	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);

	switch (key)
	{
	case KEY_RIGHT:
		animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 65, 81)));
		break;

	case KEY_LEFT:
		animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 65, 81)));
		break;

	case KEY_UP:
		animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
		break;

	case KEY_DOWN:
		animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		break;
	}

	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateIdle = Animate::create(animation);

	// run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animateIdle));
}
void Player::FireBasicBullet()
{
	AttackSystems->FireBasicBullet("Blue_Front1.png", mainSprite->getPosition(), 5000,25);
}
void Player::FireLaser()
{
	AttackSystems->FireLaserBullet("Blue_Front1.png", mainSprite->getPosition() , 10);
}
void Player::StopFiringLaser()
{
	AttackSystems->StopFiringLaser(5000, 25);
}
void Player::StopAnimation()
{
	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);

	// insert idle animation here
	animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));

	// create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateIdle = Animate::create(animation);

	// run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animateIdle));
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