#include "Player.h"
#include "Scenes/HelloWorldScene.h"
#include "AnimationHandler.h"
#include "Audio/AudioManager.h"

void Player::Init(const char* imgSource, const char* playerName, float X, float Y, Size playingSize)
{
	//remove imagesource for now
	mainSprite = Sprite::create("Blue_Front1.png");
	mainSprite->setOpacity(255.f);
    //mainSprite->setScale(0.6f);
	mainSprite->setPosition(X, Y);
	mainSprite->setName(playerName);

	mainSprite->setScale(0.5);

	auto physicsBody = PhysicsBody::createBox(
		Size(mainSprite->getContentSize().width, mainSprite->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setCategoryBitmask(2);
	physicsBody->setContactTestBitmask(1);
	physicsBody->setTag(0);
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	physicsBody->setPositionOffset(Vec2(mainSprite->getContentSize().width, mainSprite->getContentSize().height));
	mainSprite->addComponent(physicsBody);

	iFrameTimer = 2.f;
	iFrameTempTimer = 0;
	iFrameRenderTimer=0.1f;
	iFrameRenderTempTimer = 0;
	iFrameEnabled = true;
   // auto spawnpos = MoveTo::create(1, Vec2(150, 100));
    //mainSprite->runAction(spawnpos);
	fSpeed = 200.f;

	//AnimatePlayer(KEY_DOWN);
	//StopAnimation();

	charEffect = new GLProgram();
	//charEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/CharEffect.fsh");
	charEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/light.fsh");
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

	AnimHandler::GetInstance()->Init();
	AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_SPAWN, true);

	charEffect->link();
	charEffect->updateUniforms();

	this->intDirX = 0;
	this->intDirY = 0;

	lives = 1;
	score = 200;
	AttackSystems = new Attack();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    screenWidth = playingSize.width;
    screenHeight = playingSize.height;
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
    if (intDirX != 0 || intDirY != 0) {
        Vec2 playerPos = mainSprite->getPosition();
        Vec2 destination = playerPos + intDirX * Vec2(1.f, 0.f) * fSpeed * dt + intDirY * Vec2(0.f, 1.f) * fSpeed * dt;

        //destination.x = clampf(destination.x, 1.f, screenWidth - mainSprite->getContentSize().width - 1.f);
       // destination.y = clampf(destination.y, 1.f, screenHeight - mainSprite->getContentSize().height * 0.55f - 1.f);

        //auto moveEvent = MoveBy::create(0.f, intDirX * Vec2(1.f, 0.f) * fSpeed * dt);
        //mainSprite->runAction(moveEvent);
        auto moveEvent = MoveTo::create(0.f, destination);
        mainSprite->runAction(moveEvent);
    }
	if (iFrameEnabled)
	{
		iFrameUpdate(dt);
	}
    AttackSystems->LaserUpdate(dt, 10.f,
        mainSprite->getPosition());
        //mainSprite->getPosition() + Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f));
    //    mainSprite->getPosition() + (Vec2(mainSprite->getScaleX(),0) * 50));
	
	
	
	//GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(charEffect);
	//this offests the player sprite for some reason
	//mainSprite->setGLProgram(charEffect);
	//mainSprite->setGLProgramState(state);
	
	
	
	//state->setUniformVec2("loc", mLoc);

	//charEffect->
	//
	//uniform vec3  u_lightPos;
	//uniform vec2  u_contentSize;
	//uniform vec3  u_lightColor;
	//uniform vec3  u_ambientColor;
	//
	//uniform float  u_brightness;
	//uniform float u_cutoffRadius;
	//uniform float u_halfRadius;
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
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
		break;
	case KEY_UP:
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
		break;
    case KEY_DOWN:
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
		break;

	case KEY_LEFT:
		AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_BACK, true);
        return;
	}
    //AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
	
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
        mainSprite->getPosition() /*+ Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f*/,
        //mainSprite->getPosition()+Vec2(mainSprite->getScaleX()*50,0),
        300.f,25,false);
    AudioManager::GetInstance()->PlaySoundEffect("Bullet");
}
void Player::FireLaser()
{
    AttackSystems->FireLaserBullet("Projectiles/Laser.png",
		mainSprite->getPosition() - Vec2(0, -mainSprite->getContentSize().height*100));
        //mainSprite->getPosition() + Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f));
        //mainSprite->getPosition() + Vec2(mainSprite->getScaleX() * 50, 0),
        //1000);
    AudioManager::GetInstance()->PlaySoundEffect("Laser");
}
void Player::StopFiringLaser()
{
	AttackSystems->StopFiringLaser(100000, 25);
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
    else if (dirX == 0)
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
void Player::iFrameUpdate(float dt)
{
	mainSprite->getPhysicsBody()->setCollisionBitmask(0x10);
	iFrameTempTimer += dt;
	if (iFrameTempTimer <= iFrameTimer)
	{
		iFrameRenderTempTimer += dt;
		if (iFrameRenderTempTimer > iFrameRenderTimer)
		{

			if (mainSprite->getOpacity() == 0)
			{
				mainSprite->setOpacity(255);
				iFrameRenderTempTimer = 0;
			}
			else
			{
				mainSprite->setOpacity(0);
				iFrameRenderTempTimer = 0;
			}

		}
	}
	else
	{
		mainSprite->setOpacity(255);
		iFrameTempTimer = 0;
		iFrameRenderTempTimer = 0;
		iFrameEnabled = false;
	}
}
void Player::MoveCharByCoord(float X, float Y)
{
	//mainSprite->stopAllActions();
    //
	//Vector<SpriteFrame*> animFrames;
	//animFrames.reserve(4);
    //
	////animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
	////animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
	////animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
	////animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
    //
	//// create the animation out of the frames
	//Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	//Animate* animateIdle = Animate::create(animation);
    //
	//// run it and repeat it forever
	//mainSprite->runAction(RepeatForever::create(animateIdle));
    //
	//float diffX = X - mainSprite->getPosition().x;
	//float diffY = Y - mainSprite->getPosition().y;
	//Vec2 vec = Vec2(diffX, diffY);
	////Vec2 destinationPos = Vec2(X, Y);
	//auto moveEvent = MoveBy::create(vec.length() * 0.01f, vec);
	////auto moveEvent = MoveTo::create(destinationPos.length() / fSpeed, destinationPos);
    //
	//auto callbackStop = CallFunc::create([]() {
	//	//mainSprite->stopAllActions();
	//	auto scene = Director::getInstance()->getRunningScene();
	//	auto layer = scene->getChildByTag(999);
	//	HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
	//	//if (helloLayer != NULL)
	//	//	helloLayer->GetPlayer()->StopAnimation();
	//});
	//auto seq = Sequence::create(moveEvent, callbackStop, nullptr);
	//mainSprite->runAction(seq);
}