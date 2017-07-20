#include "Player.h"
#include "Scenes/HelloWorldScene.h"
#include "AnimationHandler.h"
#include "Audio/AudioManager.h"
#include "Input\input.h"

#define COCOS2D_DEBUG 1

void Player::Init(const char* imgSource, const char* playerName, float X, float Y, Size playingSize)
{
	//remove imagesource for now
	upgrade = 0;
	missiles = 0;
	powerup_max = 4;
    b_movement = true;
    b_winGame = false;

	mainSprite = Sprite::create("ship_test.png");
    //AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
	mainSprite->setOpacity(255.f);
    mainSprite->setScale(0.6f);
	//mainSprite->setAnchorPoint(Vec2(0.5f, 0.5f));


    startingPos.set(X, Y);
    mainSprite->setPosition(X, Y);

	mainSprite->setName(playerName);
	funnel_spacing = 110;

	//mainSprite->setScale(0.5);

    auto physicsBody = PhysicsBody::createBox(
        Size(0.3f * mainSprite->getContentSize().width, 0.3f * mainSprite->getContentSize().height),
       // Size(200, 100),
		PhysicsMaterial(0.1f, 0.0f, 0.0f));

    //auto physicsBody = PhysicsBody::createCircle(0.5f * mainSprite->getContentSize().height, PhysicsMaterial(0.1f, 0.0f, 0.0f));
    //CCLOG("SIZE : %4.2f ", mainSprite->getContentSize().height);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setCollisionBitmask(28);
	physicsBody->setContactTestBitmask(28);
	physicsBody->setTag(0);
	physicsBody->setDynamic(false);
	physicsBody->setGravityEnable(false);
	//physicsBody->setPositionOffset(Vec2(0, 0.3f * mainSprite->getContentSize().height));
    //CCLOG("SIZE OFFSET : %4.2f ", mainSprite->getContentSize().height);
    physicsBody->setVelocityLimit(0.f);
    mainSprite->addComponent(physicsBody);


	iFrameTimer = 2.f;
	iFrameTempTimer = 0;
	iFrameRenderTimer = 0.1f;
	iFrameRenderTempTimer = 0;
	RespawnTempTimer = 0.0f;
	RespawnTimer = 2.0f;
	Death = false;
	iFrameEnabled = false;
   // auto spawnpos = MoveTo::create(1, Vec2(150, 100));
    //mainSprite->runAction(spawnpos);
	fSpeed = 200.f;
    Respawn();
	//AnimatePlayer(KEY_DOWN);
	//StopAnimation();

	//charEffect = new GLProgram();
	///charEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/CharEffect.fsh");
	//charEffect->initWithFilenames("Shaders/Basic.vsh", "Shaders/light.fsh");
	//charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    //charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    //charEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);

	//AnimHandler::GetInstance()->Init();
	//AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_SPAWN, false);
    //Respawn();

    //charEffect->link();
    //charEffect->updateUniforms();

	this->intDirX = 0;
	this->intDirY = 0;

	lives = 1;
	score = 0;
	scoreMultiplier = 1;
	AttackSystems = new Attack("Projectiles/Laser.png");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    screenWidth = playingSize.width;
    screenHeight = playingSize.height;

    //mainSprite->getPhysicsBody()->onAdd();
}

void Player::Die()
{
    mainSprite->getPhysicsBody()->setCollisionBitmask(0);
    mainSprite->getPhysicsBody()->setContactTestBitmask(0);
    mainSprite->getPhysicsBody()->setCategoryBitmask(0);
	scoreMultiplier = 1.f;

    // reset laser
    AttackSystems->SetLaserMode(false);
    StopFiringLaser();
    

    b_movement = false;
    SetDeath(true);
    setLives(lives - 1);
}

int Player::getScore()
{
	return score;
}
//void Player::setScore(int score)
//{
//	this->score = score;
//}
void Player::Update(float dt)
{
    if (Death)
    {
        RespawnTempTimer += dt;
        mainSprite->setOpacity(0);
        if (RespawnTempTimer > 2.f)
        {
            Death = false;
            //iFrameEnabled = true;

            if (lives < 0) {
                auto scene = Director::getInstance()->getRunningScene();
                auto layer = scene->getChildByTag(999);
                HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
                helloLayer->GetGUI()->initEndScreen(this, false);
            }
            else {
                mainSprite->setOpacity(255);
                Respawn();
            }
            RespawnTempTimer = 0;
        }

        //if (RespawnTempTimer > RespawnTimer)
        //{
        //    mainSprite->setOpacity(255);
        //    Death = false;
        //    iFrameEnabled = true;
        //    RespawnTempTimer = 0;
        //}
    }
    else
	{
		if (intDirX != 0 || intDirY != 0) {
			Vec2 playerPos = mainSprite->getPosition();
			Vec2 destination = playerPos + intDirX * Vec2(1.f, 0.f) * fSpeed * dt + intDirY * Vec2(0.f, 1.f) * fSpeed * dt;

            destination.x = clampf(destination.x, 1.f, screenWidth - 0.25f * mainSprite->getContentSize().width - 1.f);
			destination.y = clampf(destination.y, 1.f, screenHeight - 1.f);

			//auto moveEvent = MoveBy::create(0.f, intDirX * Vec2(1.f, 0.f) * fSpeed * dt);
			//mainSprite->runAction(moveEvent);

			//Constrain Player
			if ((destination.x > 0 + ((mainSprite->getContentSize().width*mainSprite->getScaleX()) / 8)&& destination.x < screenWidth -(( mainSprite->getContentSize().width*mainSprite->getScaleX()) / 8)) &&
				(destination.y >0 + ((mainSprite->getContentSize().height*mainSprite->getScaleY()) / 8 )&& destination.y < screenHeight -( (mainSprite->getContentSize().height*mainSprite->getScaleY()) / 8)))
			{//player is not at boundary
				UpdateFunnels();
				auto moveEvent = MoveTo::create(0.f, destination);
				mainSprite->runAction(moveEvent);
			}
			else
			{
				Vec2 playerPos = mainSprite->getPosition();
				Vec2 destination = playerPos +(-1) *intDirX * Vec2(1.f, 0.f) * fSpeed * dt + (-1)*intDirY * Vec2(0.f, 1.f) * fSpeed * dt;
				destination.x = clampf(destination.x, 1.f, screenWidth - 0.25f * mainSprite->getContentSize().width - 1.f);
				destination.y = clampf(destination.y, 1.f, screenHeight - 1.f);
				auto moveEvent = MoveTo::create(0.f, destination);
				mainSprite->runAction(moveEvent);

			}
		}

        mainSprite->getPhysicsBody()->onAdd();

        //mainSprite->getPhysicsBody()->setVelocity(Vec2(intDirX, intDirY));
        //CCLOG("Position: %4.2f, %4.2f", mainSprite->getPosition().x, mainSprite->getPosition().y);
        //CCLOG("Veloctity: %4.2f, %4.2f", mainSprite->getPhysicsBody()->getVelocity().x, mainSprite->getPhysicsBody()->getVelocity().y);

		if (iFrameEnabled)
		{
			iFrameUpdate(dt);
		}

        // Attack Systems
        if (AttackSystems->IsLaserMode()) {
            AttackSystems->UpdateLaserTimer(dt);
            AttackSystems->LaserUpdate(dt, 10.f, mainSprite->getPosition());
            //mainSprite->getPosition() + Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f));
            //    mainSprite->getPosition() + (Vec2(mainSprite->getScaleX(),0) * 50));
        }


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

}

void Player::AnimatePlayer(KEYCODE key)
{
    if (!b_movement)
        return;

	mainSprite->stopAllActions();
	//AnimHandler::getInstance()->Init();
	//Vector<SpriteFrame*> animFrames;
	//animFrames.reserve(4);

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
	AttackSystems->FireBasicBullet("Projectiles/ship_bullet.png",
        mainSprite->getPosition() /*+ Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f*/,
        //mainSprite->getPosition()+Vec2(mainSprite->getScaleX()*50,0),
        3000.f,1.5,false);
}
void Player::FireLaser()
{
	//Upgrade();
    AttackSystems->FireLaserBullet(mainSprite->getPosition() - Vec2(0, -mainSprite->getContentSize().height*100));
        //mainSprite->getPosition() + Vec2(mainSprite->getContentSize().width * 0.5f * 0.6f, mainSprite->getContentSize().height * 0.5f * 0.6f));
        //mainSprite->getPosition() + Vec2(mainSprite->getScaleX() * 50, 0),
        //1000);
}
void Player::StopFiringLaser()
{
	AttackSystems->StopFiringLaser(/*100000, 1*/);
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
    mainSprite->getPhysicsBody()->setCollisionBitmask(0);
    mainSprite->getPhysicsBody()->setContactTestBitmask(0);
    mainSprite->getPhysicsBody()->setCategoryBitmask(0);
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
		mainSprite->getPhysicsBody()->setCollisionBitmask(28);
		mainSprite->getPhysicsBody()->setContactTestBitmask(28);
		mainSprite->getPhysicsBody()->setCategoryBitmask(1);
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

void Player::UpdateFunnels()
{
	if (upgrade < 1)
		return;
	//funnel_list[1];
	//int count = sizeof(funnel_list) / sizeof(funnel_list[0]);
	for (int i = 0; i <= upgrade-1; i++)
	{


		Vec2 displacement = funnel_list[i]->_eSprite->getPosition();
		if (i == 0)
		{		
			if (displacement.getDistanceSq(mainSprite->getPosition()) > funnel_spacing*funnel_spacing)
			{
				Vec2 destination = (mainSprite->getPosition() - displacement).getNormalized() * 5;
				auto moveEvent = MoveBy::create(0.2f, destination);
				funnel_list[i]->_eSprite->runAction(moveEvent);
			}
			continue;
		}
		else
		{
			if (displacement.getDistanceSq(funnel_list[i-1]->_eSprite->getPosition()) > funnel_spacing*funnel_spacing)
			{
				Vec2 destination = (funnel_list[i - 1]->_eSprite->getPosition() - displacement).getNormalized() * 5;
				auto moveEvent = MoveBy::create(0.2f, destination);
				funnel_list[i]->_eSprite->runAction(moveEvent);

			}


		}
	}
}
void Player::Upgrade()
{
	if (upgrade >= powerup_max)
		return;

	pfunnel* funnel = new pfunnel;
	funnel->_eSprite->setPosition(mainSprite->getPosition());
	funnel_list[upgrade] = funnel;
	auto scene = Director::getInstance()->getRunningScene();
	scene->addChild(funnel->_eSprite);
	funnel->RunAttack();
	upgrade++;
}
void Player::Respawn()
{
	
	for (int i = 0; i <= upgrade - 1; i++)
	{
		funnel_list[i]->_eSprite->stopAllActions();
		funnel_list[i]->_eSprite->removeFromParentAndCleanup(true);
		delete funnel_list[i];
	}
	upgrade = 0;
	missiles = 0;
    mainSprite->setPosition(startingPos.x, startingPos.y);

    mainSprite->stopAllActions();
    AnimHandler::GetInstance()->setCCAnimation(mainSprite, AnimHandler::SHIP_SPAWN, CallFunc::create(CC_CALLBACK_0(Player::SetiFrames/*Player::CompleteRespawn*/, this)));
}

void Player::SetiFrames()
{
    AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE,true);
    b_movement = true;
    //Death = true;
    iFrameRenderTimer = 0;
    iFrameEnabled = true;
}

void Player::CompleteRespawn()
{
    AnimHandler::GetInstance()->setAnimation(mainSprite, AnimHandler::SHIP_IDLE, true);
    b_movement = true;

    mainSprite->getPhysicsBody()->setCollisionBitmask(28);
    mainSprite->getPhysicsBody()->setContactTestBitmask(28);
    mainSprite->getPhysicsBody()->setCategoryBitmask(1);
}