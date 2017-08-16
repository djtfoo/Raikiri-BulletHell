#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "FreezeTimeScene.h"

#include "GameInputManager.h"
#include "AudioManager.h"
#include "AnimationHandler.h"
#include "BConstruct.h"
#include "Powerup.h"
#include "Shield.h"
#include "Explosion.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	//Scene::
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
	//scene->addChild(GUILayer,0, 997);
    scene->addChild(layer, 0, 999);

    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//LoadEnemies();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	//this->schedule(schedule_selector(HelloWorld::update), 1.0);
	this->scheduleUpdate();
	
	//GUI
	//auto GUIlayer = this->getChildByTag(997);

	default_scale = 1600;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	playingSize = Size(visibleSize.width, visibleSize.height);
	AnimHandler::GetInstance()->Init();

	//sprite stuff
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ship_idle.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ship_spawn.plist");

	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");
	//bg
	currbg = 0;

	//bg_sprite1 = Sprite::create("moon_b_1.png");
	bg_sprite1 = Sprite::create("moonnight_b_1.png");
	bg_sprite1->setScale(1.3);
	bg_sprite1->setAnchorPoint(Vec2::ZERO);
	
	bg_sprite1->setPosition(0, 0);
	bg_sprite1->setName("bg1");
	

	bg_sprite2 = Sprite::create("moonnight_b_1.png");
	bg_sprite2->setScale(1.3);
	bg_sprite2->setAnchorPoint(Vec2::ZERO);
	
	bg_sprite2->setPosition(0, 0);
	bg_sprite2->setName("bg2");


 	this->addChild(bg_sprite1, -2);
	this->addChild(bg_sprite2, -2);


	float scrollspeed = 25;
	auto spriteAction = RepeatForever::create(MoveBy::create(scrollspeed, Vec2(-playingSize.width, 0)));
	auto spriteAction2 = RepeatForever::create(MoveBy::create(scrollspeed, Vec2(-playingSize.width, 0)));
	bg_sprite1->runAction(spriteAction);
	bg_sprite2->runAction(spriteAction2);

	//auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	//sprite->setAnchorPoint(Vec2::ZERO);
	//sprite->setPosition(0, 0);
	//float spriteWidth = sprite->getContentSize().width;
	//int numOfTiles = std::ceil(visibleSize.width / spriteWidth);	// get the larger number after dividing; so there will be excess
	////nodeItems->addChild(sprite, 0);
	//for (int i = 0; i < numOfTiles; ++i) {
	//	auto tempSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
	//	tempSprite->setAnchorPoint(Vec2::ZERO);
	//	tempSprite->setPosition(i * spriteWidth, 0);
	//	nodeItems->addChild(tempSprite, 0);
	//}

	nodeItems->setPosition(0, visibleSize.height / 2 - (visibleSize.height / 8));
	this->addChild(nodeItems, 1);

    // sprite node
    spriteNode = Node::create();
    spriteNode->setName("spriteNode");
    this->addChild(spriteNode, 1);

	pwNode = Node::create();
	pwNode->setName("powerNode");
	this->addChild(pwNode, 2);
	// player sprites
	//auto spriteNode = Node::create();
	
  /*  projectieNode = Node::create();
    projectieNode->setName("projectileNode");
    this->addChild(projectieNode, 2);*/
	//Vector<SpriteFrame*> frames = getAnimation("ship_idle%04d.png", 15);
//	auto mainSprite = Sprite::create();
//	AnimHandler::getInstance()->setAnimation(mainSprite, AnimHandler::CONSTRUCT_ACTIVEP2, true);
//	//auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 20);//Xseconds/Yframes (Yframes per second)
//	mainSprite->runAction(RepeatForever::create(Animate::create(animation)));
//
//	mainSprite->setAnchorPoint(Vec2::ZERO);
//	mainSprite->setPosition(100, visibleSize.height / 2 - (visibleSize.height / 8) + sprite->getContentSize().height);
//	mainSprite->setName("mainSprite");

	//this->addChild(spriteNode, 1);
	//spriteNode->addChild(mainSprite, 1);
	//// move the psrite
	//auto moveEvent = MoveBy::create(5, Vec2(200, 0));	// move that distance within 5 seconds; relative movement
	////auto moveEvent = MoveTo::create(5, Vec2(200, 0));	// move to that coordinate within 5 seconds
	////mainSprite->runAction(moveEvent);
	//
	//// patrol back and forth
	//auto delay = DelayTime::create(5.f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//mainSprite->runAction(sequence);
	//mainSprite->runAction(sequence->reverse());


	//ship stuff(trying from spritesheet)
	// sprite

	//Entity* entity = new Entity;
	//entity->SettoSpawn();
	//temp player

    // PLAYER
    mainPlayer = new Player();
    //mainPlayer->SetLightEffect(lightEffect);
    mainPlayer->Init("Blue_Front1.png", "Player", 300, 300, playingSize);
	//AnimHandler::getInstance()->setAnimation(mainPlayer->GetSprite(), AnimHandler::SHIP_IDLE, true);
    this->addChild(mainPlayer->GetSprite(), 1);
	this->addChild(mainPlayer->_emitter,-1);
    //this->addChild(spriteNode, 1);

    mainPlayer->GetAttackSystems()->InitialiseLaser(playingSize, spriteNode);



    proPostProcess = new GLProgram();
    proPostProcess->GLProgram::initWithFilenames("Shaders/Basic.vsh", "Shaders/Grayscale.fsh");
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_POSITION);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_COLOR);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
    proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);

    proPostProcess->link();
    proPostProcess->updateUniforms();

    rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
    rendtex->retain();

    rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
    rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
    rendtexSprite->setAnchorPoint(Point::ZERO);
    rendtexSprite->setPosition(Point::ZERO);
    rendtexSprite->setFlippedY(true);
    rendtexSprite->setGLProgram(proPostProcess);

    this->addChild(rendtexSprite, 2);

    GameInputManager::GetInstance()->Init();

    // ENEMY

	// enemy sprites
	LoadEnemies();

	
	// cannot use same event variable for multiple objects; use CloneBy

    // Listeners
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	auto listener2 = EventListenerMouse::create();
	listener2->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
  
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	auto collisionListener = EventListenerPhysicsContact::create();
	collisionListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    collisionListener->onContactSeparate = CC_CALLBACK_1(HelloWorld::onContactSeparate, this);

	//collisionListener->onContactPreSolve = CC_CALLBACK_1(HelloWorld::onContactPreSolve, this);
	//collisionListener->onContactPostSolve = CC_CALLBACK_3(HelloWorld::onContactPostSolve, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener,this);
	//schedule(CC_SCHEDULE_SELECTOR(HelloWorld::tick), 0.3f);
    // GUI
	playerGui = GUI::createPlayerGUI(mainPlayer);
	//mainPlayer->SetPlayerGUI(playerGui);
	this->addChild(playerGui, 2);

    // Audio
    AudioManager::GetInstance()->PlayBackgroundMusic("Game");

    // Freeze Time Post-Processing
    timeStopped = false;
    freezeAnimationChange = false;
    freezeAttack = false;
    freezeAttackTimer = 0.f;
    freezeAttackDashDuration = 0.f;

    screenMin.setZero();
    screenMax.set(visibleSize.width, visibleSize.height + 10.f);
    xPos = yPos = 0.f;
    widthX = heightY = 0.f;

	return true;
}

void HelloWorld::ExitScene()
{
    waveSpawner->eNode->removeAllChildrenWithCleanup(true);
    spriteNode->removeAllChildrenWithCleanup(true);
    Powerup::ClearPowerupPool();

    Shield::playerShield = NULL;

    delete mainPlayer;

    this->removeAllChildrenWithCleanup(true);
    this->onExit();
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    /*EventMouse* mouseEvent = (EventMouse*)event;
    TOUCH_TYPE mousetype;*/

    //EventTouch* touchEvent = (EventTouch*)event;
    
    Vec2 touchLocation = touch->getLocation();
    mainPlayer->prevTouchPosition = touchLocation;
    mainPlayer->SetTouchBegan(true);

    return true;
}
void  HelloWorld::onTouchMoved(Touch* touch, Event * event)
{
    Vec2 touchLocation = touch->getLocation();

    // move here
    if (mainPlayer->b_movement) {
        //auto moveEvent = MoveBy::create(0.f, (touchLocation - mainPlayer->prevTouchPosition));
        //mainPlayer->mainSprite->runAction(moveEvent);

        Vec2 playerPos = mainPlayer->GetSprite()->getPosition();

        Vec2 destination = playerPos + touchLocation - mainPlayer->prevTouchPosition;
        mainPlayer->SetMovementConstrain(destination);

        auto moveEvent = MoveTo::create(0.f, destination);
        mainPlayer->mainSprite->runAction(moveEvent);
    }

    mainPlayer->prevTouchPosition = touchLocation;  // set this position for the next frame
}
void  HelloWorld::onTouchEnded(Touch* touch, Event * event)
{
    //Vec2 touchLocation = touch->getLocation();
    mainPlayer->SetTouchBegan(false);

}
// Keyboard input
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    GameInputManager::GetInstance()->WhenKeyPressed(Input::EventKeyboardToKeycode(keyCode), mainPlayer);
}
Node* HelloWorld::getSpriteNode()
{
	return spriteNode;
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
 {
    GameInputManager::GetInstance()->WhenKeyReleased(Input::EventKeyboardToKeycode(keyCode), mainPlayer);
}

// Mouse input
//void HelloWorld::tick(float dt)
//{
//	auto sprite1 = addSpriteAtPosition(Vec2(s_centre.x + cocos2d::random(-300, 300),
//		s_centre.y + cocos2d::random(-300, 300)));
//	auto physicsBody = sprite1->getPhysicsBody();
//	physicsBody->setVelocity(Vec2(cocos2d::random(-500, 500), cocos2d::random(-500, 500)));
//	physicsBody->setContactTestBitmask(0xFFFFFFFF);
//}
void HelloWorld::LoadEnemies()
{
	auto enemynode = Node::create();
	enemynode->setName("eNode");
	this->addChild(enemynode, 1);


	waveSpawner = new WaveSpawner();	//order is important here
	waveSpawner->Init();
	waveSpawner->SetScreenBoundaries(playingSize.height, playingSize.width);
	waveSpawner->LoadFile("WaveData/testwave.csv");


	waveSpawner->SeteNode(enemynode);
}
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
  	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
//	bodyA->getNode()->getcom
	if (bodyA->getTag() == ENEMY && bodyB->getTag() == PLAYERPROJ)
	{
		Entity* entity = waveSpawner->GetEntity(bodyA->getNode());
        if (entity != NULL)
        {
            entity->TakeDamage(30);

            if (waveSpawner->GetEntity(bodyA->getNode())->IsDead())
            {
                if (mainPlayer->GetAttackSystems()->IsLaserMode()) {
                    mainPlayer->GetAttackSystems()->DeleteFromLaserVector(entity);
                }

                AudioManager::GetInstance()->PlaySoundEffect("Destruction");

                if (entity->_type == Entity::BCONSTRUCT)
                {
                    mainPlayer->SetWinGame(true);
                    playerGui->initEndScreen(mainPlayer, true);
                }
				Explosion* ex = new Explosion;
				ex->GenerateExplosion(entity->_eSprite->getPosition());
                mainPlayer->AddScore();
                mainPlayer->AddScoreMultiplier(0.2);
                playerGui->UpdateScoreMultiplierLabel(mainPlayer->GetScoreMultiplier());
                playerGui->UpdateScoreLabel(mainPlayer->getScore());
                Powerup::SetToSpawnPowerup(true);
                Powerup::SetSpawnPos(bodyA->getPosition());

                waveSpawner->DestroyEnemy(bodyA->getNode());
                //bodyA->removeFromWorld();
                bodyA->getNode()->removeFromParentAndCleanup(true);
			
            }
            ///    delete bodyA->getNode();
            //bodyB->removeFromWorld();
            if (bodyB->getNode() == NULL)
                return false;
            bodyB->getNode()->removeFromParentAndCleanup(true);

            // increase charge bar
            if (!mainPlayer->GetAttackSystems()->IsChargeBarMax())
            {
                mainPlayer->GetAttackSystems()->IncreaseChargeBarValue(5);
                playerGui->UpdateSpecialBarFill(mainPlayer->GetAttackSystems()->GetChargeBarPercentage());
            }

            //mainPlayer->
            return true;
        }
	}
	else if (bodyB->getTag() == ENEMY &&  bodyA->getTag() == PLAYERPROJ)
	{
		Entity* entity = waveSpawner->GetEntity(bodyB->getNode());
        if (entity != NULL)
        {
            entity->TakeDamage(30);

            if (waveSpawner->GetEntity(bodyB->getNode())->IsDead())
            {
                if (mainPlayer->GetAttackSystems()->IsLaserMode()) {
                    mainPlayer->GetAttackSystems()->DeleteFromLaserVector(entity);
                }

                AudioManager::GetInstance()->PlaySoundEffect("Destruction");
				Explosion* ex = new Explosion;
				ex->GenerateExplosion(entity->_eSprite->getPosition());
                if (entity->_type == Entity::BCONSTRUCT)
                {
                    mainPlayer->SetWinGame(true);
                    playerGui->initEndScreen(mainPlayer, true);
                }
                mainPlayer->AddScore();
                mainPlayer->AddScoreMultiplier(0.2);
                playerGui->UpdateScoreMultiplierLabel(mainPlayer->GetScoreMultiplier());
                playerGui->UpdateScoreLabel(mainPlayer->getScore());
                Powerup::SetToSpawnPowerup(true);
                Powerup::SetSpawnPos(bodyB->getPosition());

                waveSpawner->DestroyEnemy(bodyB->getNode());
                //bodyB->removeFromWorld();
                bodyB->getNode()->removeFromParentAndCleanup(true);
            }
            //bodyA->removeFromWorld();
            if (bodyA->getNode() == NULL)
                return false;
            bodyA->getNode()->removeFromParentAndCleanup(true);
            //      delete bodyA->getNode();

            // increase charge bar
            if (!mainPlayer->GetAttackSystems()->IsChargeBarMax())
            {
                mainPlayer->GetAttackSystems()->IncreaseChargeBarValue(10);
                playerGui->UpdateSpecialBarFill(mainPlayer->GetAttackSystems()->GetChargeBarPercentage());
            }

            return true;
        }
	}
	else if (bodyA->getTag() == PLAYER && bodyB->getTag() == ENEMYPROJ)
	{
        if (!freezeAttack && !mainPlayer->GetiFrames())
        {
           
			//if (mainPlayer->getLives() < 0)
			//	playerGui->initEndScreen(mainPlayer);
			playerGui->UpdateScoreMultiplierLabel(mainPlayer->GetScoreMultiplier());
			playerGui->UpdateLivesLabel(std::to_string(mainPlayer->getLives()).c_str());
            bodyB->getNode()->removeFromParentAndCleanup(true);
			mainPlayer->Die();
            return true;
        }
        return false;
	}
	else if (bodyB->getTag() == PLAYER && bodyA->getTag() == ENEMYPROJ)
	{
        if (!freezeAttack && !mainPlayer->GetiFrames())
        {
           
            //mainPlayer->SetDeath(true);
            //mainPlayer->setLives(mainPlayer->getLives() - 1);
			//if (mainPlayer->getLives() < 0)
			//	playerGui->initEndScreen(mainPlayer);
			playerGui->UpdateScoreMultiplierLabel(mainPlayer->GetScoreMultiplier());
			playerGui->UpdateLivesLabel(std::to_string(mainPlayer->getLives()).c_str());
            bodyA->getNode()->removeFromParentAndCleanup(true);
			mainPlayer->Die();
            return true;
        }
        return false;
	}

    // collision for attacks
    else if (bodyA->getTag() == PLAYER && bodyB->getTag() == ENEMY)
    {
        if (freezeAttack)   // player is in freeze special attack
        {
            // play hit SFX
            AudioManager::GetInstance()->PlaySoundEffect("DashHit");

            // deal damage to entity
            Entity* entity = waveSpawner->GetEntity(bodyB->getNode());
            if (!mainPlayer->GetAttackSystems()->HasDashHitEntity(entity))   // not hit before
            {
                entity->TakeDamage(500);

                if (entity->IsDead())
                {
					Explosion* ex = new Explosion;
					ex->GenerateExplosion(entity->_eSprite->getPosition());
					if (entity->_type == Entity::BCONSTRUCT)
					{
                        mainPlayer->SetWinGame(true);
						playerGui->initEndScreen(mainPlayer, true);
						mainPlayer->AddScoreMultiplier(10);
					}
					mainPlayer->AddScoreMultiplier(1.0);
					mainPlayer->AddScore();
				//	mainPlayer->AddScoreMultiplier(0.2);
					playerGui->UpdateScoreMultiplierLabel(mainPlayer->GetScoreMultiplier());
					playerGui->UpdateScoreLabel(mainPlayer->getScore());
                    Powerup::SetToSpawnPowerup(true);
                    Powerup::SetSpawnPos(bodyB->getPosition());

                    waveSpawner->DestroyEnemy(bodyB->getNode());
                    //bodyB->removeFromWorld();
                    bodyB->getNode()->removeFromParentAndCleanup(true);
                }
                else
                {
                    // add to temp hit entities list so it cannot be hit again
                    mainPlayer->GetAttackSystems()->AddDashHitEntity(entity);
                }
            }

            Sprite* sparkle = Sprite::create("Attack/hit_sparkle.png");
            sparkle->setAnchorPoint(Vec2(0.5f, 0.5f));
            sparkle->setPosition(bodyB->getPosition());

            auto moveEvent = MoveTo::create(1.f, bodyB->getPosition());
            auto callbackFunc = CallFunc::create([sparkle]() {
                sparkle->removeFromParentAndCleanup(true);
            });
            auto seq = Sequence::create(moveEvent, callbackFunc, nullptr);
            sparkle->runAction(seq);

            spriteNode->addChild(sparkle, 1);
        }
        else
        {
            // player loses 1 life

        }
    }
    else if (bodyB->getTag() == PLAYER && bodyA->getTag() == ENEMY)
    {
        if (freezeAttack)   // player is in freeze special attack
        {
            // play hit SFX
            AudioManager::GetInstance()->PlaySoundEffect("DashHit");

            // deal damage to entity
            Entity* entity = waveSpawner->GetEntity(bodyA->getNode());
            if (!mainPlayer->GetAttackSystems()->HasDashHitEntity(entity))   // not hit before
            {
                entity->TakeDamage(500);

                if (entity->IsDead())
                {
					if (entity->_type == Entity::BCONSTRUCT)
					{
                        mainPlayer->SetWinGame(true);
						playerGui->initEndScreen(mainPlayer, true);
						mainPlayer->AddScoreMultiplier(10);
					}
					mainPlayer->AddScoreMultiplier(1.0);
					mainPlayer->AddScore();
					playerGui->UpdateScoreMultiplierLabel(mainPlayer->GetScoreMultiplier());
					playerGui->UpdateScoreLabel(mainPlayer->getScore());
                    Powerup::SetToSpawnPowerup(true);
                    Powerup::SetSpawnPos(bodyA->getPosition());

                    waveSpawner->DestroyEnemy(bodyA->getNode());
                    //bodyB->removeFromWorld();
                    bodyA->getNode()->removeFromParentAndCleanup(true);
                }
                else
                {
                    // add to temp hit entities list so it cannot be hit again
                    mainPlayer->GetAttackSystems()->AddDashHitEntity(entity);
                }
            }

            Sprite* sparkle = Sprite::create("Attack/hit_sparkle.png");
            sparkle->setAnchorPoint(Vec2(0.5f, 0.5f));
            sparkle->setPosition(bodyA->getPosition());

            auto moveEvent = MoveTo::create(1.f, bodyB->getPosition());
            auto callbackFunc = CallFunc::create([sparkle]() {
                sparkle->removeFromParentAndCleanup(true);
            });
            auto seq = Sequence::create(moveEvent, callbackFunc, nullptr);
            sparkle->runAction(seq);

            spriteNode->addChild(sparkle, 1);
        }
        else
        {
            // player loses 1 life

        }
    }
	
	// POWERUP

	else if (bodyA->getTag() == POWERUP && bodyB->getTag() == PLAYER)
	{
		Powerup::FindAndBeginPickup(bodyA->getNode(), bodyA->getPosition());
		return true;
	}
	else if (bodyB->getTag() == POWERUP && bodyA->getTag() == PLAYER)
	{
		Powerup::FindAndBeginPickup(bodyB->getNode(), bodyA->getPosition());
		return true;
	}
	
    // SHIELD
    else if (bodyA->getTag() == ENEMYPROJ && bodyB->getTag() == PLAYERSHIELD)
    {
        // set to destroy Shield
        Shield::SetDestroyPlayerShield();

        bodyA->getNode()->removeFromParentAndCleanup(true);
        //bodyB->getNode()->removeFromParentAndCleanup(false);
    }
    else if (bodyA->getTag() == PLAYERSHIELD && bodyB->getTag() == ENEMYPROJ)
    {
        // set to destroy Shield
        Shield::SetDestroyPlayerShield();

        //bodyA->getNode()->removeFromParentAndCleanup(false);
        bodyB->getNode()->removeFromParentAndCleanup(true);
    }
	//Laser
	else if (bodyA->getTag() == LASERPOWERUP && bodyB->getTag() == ENEMY)
	{
        mainPlayer->GetAttackSystems()->AddToLaserVector(waveSpawner->GetEntity(bodyB->getNode()), bodyB->getNode());
	}
	else if (bodyB->getTag() == LASERPOWERUP && bodyA->getTag() == ENEMY)
	{
        mainPlayer->GetAttackSystems()->AddToLaserVector(waveSpawner->GetEntity(bodyA->getNode()), bodyA->getNode());
	}

	return true;
}
//bool HelloWorld::onContactPreSolve(PhysicsContact& contact)
//{
//	auto bodyA = contact.getShapeA()->getBody();
//	auto bodyB = contact.getShapeB()->getBody();
//	return true;
//}
//bool HelloWorld::onContactPostSolve(PhysicsContact& contact)
//{
//	auto bodyA = contact.getShapeA()->getBody();
//	auto bodyB = contact.getShapeB()->getBody();
//	return true;
//}

bool HelloWorld::onContactSeparate(PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();

    if (bodyA->getTag() == LASERPOWERUP && bodyB->getTag() == ENEMY)
    {
        mainPlayer->GetAttackSystems()->DeleteFromLaserVector(waveSpawner->GetEntity(bodyB->getNode()));
    }
    else if (bodyB->getTag() == LASERPOWERUP && bodyA->getTag() == ENEMY)
    {
        mainPlayer->GetAttackSystems()->DeleteFromLaserVector(waveSpawner->GetEntity(bodyA->getNode()));
    }

	return true;
}
void HelloWorld::onMouseDown(Event* event)
{
    EventMouse* mouseEvent = (EventMouse*)event;
    TOUCH_TYPE mousetype;

    switch (mouseEvent->getMouseButton())
    {
    case 0: // left mouse
        mousetype = TOUCH_MOUSELEFT;
        break;
    case 1: // right mouse
        mousetype = TOUCH_MOUSERIGHT;
        break;
    }

    Input::SetMouseState(mousetype, TOUCH_HELD);
}

void HelloWorld::onMouseUp(Event* event)
{
    EventMouse* mouseEvent = (EventMouse*)event;
    TOUCH_TYPE mousetype;

    switch (mouseEvent->getMouseButton())
    {
    case 0: // left mouse
        mousetype = TOUCH_MOUSELEFT;
        break;
    case 1: // right mouse
        mousetype = TOUCH_MOUSERIGHT;
        break;
    }

    Input::SetMouseState(mousetype, TOUCH_RELEASED);
    Input::SetMousePos(mousetype, Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY()));
}


void HelloWorld::update(float dt)
{
	//auto currSprite = this->getChildByName("spriteNode")->getChildByName("bg1");
	//Vec2 pos;
	//pos = currSprite->getPosition;
	
	waveSpawner->Run(dt);
	mainPlayer->Update(dt);

    if (freezeAttack)
        UpdateFreezeAttack(dt);

    //======================
    // Scrolling Background
    //======================
	if (bg_sprite1->getPositionX() <= ((-bg_sprite1->getContentSize().width*1.3) + playingSize.width+3) && currbg ==0)
	{
		currbg = 1;
		bg_sprite2->setPosition(playingSize.width, 0);
		//bg_sprite1->setPosition(playingSize.width, -playingSize.height);
	}
	if (bg_sprite2->getPositionX() <= ((-bg_sprite1->getContentSize().width*1.3) + playingSize.width+3 )&& currbg ==1)
	{
		//bg_sprite2->setPosition(playingSize.width, -playingSize.height);
		bg_sprite1->setPosition(playingSize.width, 0);
		currbg = 0;
	}

    //=========
    // Shields
    //=========
    // Update Shields
    if (Shield::playerShield != NULL)
        Shield::playerShield->UpdatePosition();
    for (std::map<Entity*, Shield*>::iterator it = Shield::entityShieldsList.begin(); it != Shield::entityShieldsList.end(); ++it)
    {
        it->second->UpdatePosition();
    }

    // Spawn Shield
    if (Shield::ToSpawnShield())
    {
        Shield::SpawnShield();
        Shield::SetToSpawnShield(false);
    }

    // Destroy Shield
    if (Shield::IsToDestroy())
    {
        Shield::DestroyShield();
    }

    //===========
    // Power-Ups
    //===========
    Powerup::PowerupsUpdate();

	// Spawn Power-up
	if (Powerup::ToSpawnPowerup())
	{
		if (Powerup::CheckSpawnPowerup())
			Powerup::RandomSpawnPowerup();

		Powerup::SetToSpawnPowerup(false);
	}
	// Destroy Power-up
	if (Powerup::IsToDestroy())
	{
		Powerup::DestroyPickedups();
	}

    //Input::GetInstance()->Update(dt);

    //========================
    // Post-processing shader
    //========================
    if (freezeAnimationChange) {
        UpdateFreezeAnimation(dt);
    }

    rendtex->beginWithClear(.0f, .0f, .0f, .0f);
    this->visit();
    rendtex->end();
    rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    rendtexSprite->setPosition(xPos, yPos);
    if (timeStopped) {
        rendtexSprite->setPosition(xPos, yPos);
        rendtexSprite->setGLProgram(proPostProcess);    // apply grayscale effect
    }
    else {
        rendtexSprite->setPosition(0.f, 0.f);
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
Vec2 HelloWorld::ScreenToWorld(Vec2 pos)
{
	float screen_scaling = (playingSize.width / default_scale);
	Vec2 result = pos*screen_scaling;
	return result;

}

Vector<cocos2d::SpriteFrame*> HelloWorld::getAnimation(const char *format, int count)
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

void HelloWorld::ExecuteFreezeTime()
{
	if (!freezeAnimationChange) {
        freezeAnimationChange = true;
		//timeStopped = !timeStopped;
        if (timeStopped)
        {
            timeStopped = false;
            //xPos = mainPlayer->GetSprite()->getPosition().x;
            //yPos = mainPlayer->GetSprite()->getPosition().y;
        }
        else
        {
            timeStopped = true;
            //xPos = mainPlayer->GetSprite()->getPosition().x;
            //yPos = mainPlayer->GetSprite()->getPosition().y;

            xPos = mainPlayer->GetSprite()->getPosition().x;
            yPos = mainPlayer->GetSprite()->getPosition().y;
            widthX = 0.f;
            heightY = 0.f;
        }
	}
}

static float freezeSpeed = 3000.f;
void HelloWorld::UpdateFreezeAnimation(float dt)
{
    float deltaChange = freezeSpeed * dt;
    bool doneFreezing = true;

    if (timeStopped) {
        if (xPos > screenMin.x) {
            xPos -= deltaChange;
            doneFreezing = false;
        }
        else {
            xPos = screenMin.x;
        }

        if (yPos > screenMin.y) {
            yPos -= deltaChange;
            doneFreezing = false;
        }
        else {
            yPos = screenMin.y;
        }

        if (widthX < screenMax.x) {
            widthX += deltaChange;
            doneFreezing = false;
        }
        else {
            widthX = screenMax.x;
        }

        if (heightY < screenMax.y) {
            heightY += deltaChange;
            doneFreezing = false;
        }
        else {
            heightY = screenMax.y;
        }
    }
    else {
        //if (minX < mainPlayer->GetSprite()->getPosition().x)
        //    minX -= deltaChange;
        //else if (minX > mainPlayer->GetSprite()->getPosition().x)
        //    minX = mainPlayer->GetSprite()->getPosition().x;
        //
        //if (minY > mainPlayer->GetSprite()->getPosition().y)
        //    minY -= deltaChange;
        //else if (minY > mainPlayer->GetSprite()->getPosition().y)
        //    minY = mainPlayer->GetSprite()->getPosition().y;
        //+
        //if (maxX > mainPlayer->GetSprite()->getPosition().x)
        //    maxX += deltaChange;
        //else if (maxX < mainPlayer->GetSprite()->getPosition().x)
        //    maxX = mainPlayer->GetSprite()->getPosition().x;
        //
        //if (maxY > mainPlayer->GetSprite()->getPosition().y)
        //    maxY += deltaChange;
        //else if (maxY < mainPlayer->GetSprite()->getPosition().y)
        //    maxY = mainPlayer->GetSprite()->getPosition().y;
    }

    //rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
    rendtexSprite->setTextureRect(Rect(xPos, yPos, widthX, heightY));

    if (doneFreezing)
    {
        freezeAnimationChange = false;
        if (timeStopped)
        {
            freezeAttack = true;
            freezeAttackTimer = 1.f;

            // create freeze scene
            //CCDirector::getInstance()->pause();
            Scene* scene = FreezeTime::createScene(rendtexSprite);
            scene->init();
            CCDirector::getInstance()->pushScene(scene);
        }
    }
}
//Node* HelloWorld::getProjectileNode()
//{
//    return projectieNode;
//}

void HelloWorld::SetPlayerDashPoints(const std::vector<Vec2>& points)
{
    mainPlayer->GetAttackSystems()->SetDashLinePoints(points);
}

const static float dashSpeed = 20000.f;
void HelloWorld::UpdateFreezeAttack(float dt)
{
    if (FreezeTime::dashLinePoints.empty())
    {
        freezeAttack = false;
        ExecuteFreezeTime();
        mainPlayer->GetAttackSystems()->ClearDashHitEntities();

        // clear charge bar
        if (FreezeTime::chargeUsed) {
            mainPlayer->GetAttackSystems()->ResetChargeBarValue();
            playerGui->UpdateSpecialBarFill(mainPlayer->GetAttackSystems()->GetChargeBarPercentage());
        }
        return;
    }

    freezeAttackTimer += dt;
    if (freezeAttackTimer > freezeAttackDashDuration)
    {
        freezeAttackTimer = 0.f;

        Vec2 distance = FreezeTime::dashLinePoints[0] - mainPlayer->GetSprite()->getPosition();
        freezeAttackDashDuration = distance.length() / dashSpeed;   // this is the duration of the dash itself

        auto moveEvent = MoveTo::create(freezeAttackDashDuration, FreezeTime::dashLinePoints[0]);
        mainPlayer->GetSprite()->runAction(moveEvent);
        //mainPlayer->GetSprite()->getPhysicsBody()->setVelocity(0.f);

        // increase duration by a buffer time
        freezeAttackDashDuration += 0.03f;

        // remove first point
        FreezeTime::dashLinePoints.erase(FreezeTime::dashLinePoints.begin());
    }
}

void HelloWorld::SetGrayscale()
{
    timeStopped = true;

    xPos = screenMin.x;
    yPos = screenMin.y;
    widthX = screenMax.x;
    heightY = screenMax.y;

    rendtexSprite->setTextureRect(Rect(xPos, yPos, widthX, heightY));
}