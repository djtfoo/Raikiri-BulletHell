#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "Input/GameInputManager.h"
#include "Audio/AudioManager.h"
#include "AnimationHandler.h"

#include "Powerup/Powerup.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
	//scene->addChild(GUILayer,0, 997);
    scene->addChild(layer, 0, 999);

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
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	AnimHandler::GetInstance()->Init();

	//sprite stuff
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ship_idle.plist");
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ship_spawn.plist");

	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	//bg
	currbg = 0;

	bg_sprite1 = Sprite::create("moon_b_1.png");
	bg_sprite1->setPosition(0, -playingSize.height);
	bg_sprite1->setAnchorPoint(Vec2::ZERO);
	bg_sprite1->setName("bg1");
	bg_sprite2 = Sprite::create("moon_b_1.png");
	bg_sprite2->setAnchorPoint(Vec2::ZERO);
	bg_sprite2->setPosition(bg_sprite1->getContentSize().width, -playingSize.height);
	bg_sprite2->setName("bg2");

	nodeItems->addChild(bg_sprite1, 0);
	nodeItems->addChild(bg_sprite2, 0);


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

	// player sprites
	//auto spriteNode = Node::create();
	spriteNode = Node::create();
	spriteNode->setName("spriteNode");
	this->addChild(spriteNode, 1);

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

	// Lighting
	lightEffect = LightEffect::create();
	lightEffect->retain();

	Vec3 lightPos(visibleSize.width * 0.5f, visibleSize.height * 0.5f, 100.f);
	lightEffect->setLightPos(lightPos);
	lightEffect->setLightCutoffRadius(1000.f);
	lightEffect->setBrightness(2.f);
	//Entity* entity = new Entity;
	//entity->SettoSpawn();
	//temp player

    // PLAYER
    mainPlayer = new Player();
    mainPlayer->SetLightEffect(lightEffect);
    mainPlayer->Init("Blue_Front1.png", "Player", 300, 300, playingSize);
	//AnimHandler::getInstance()->setAnimation(mainPlayer->GetSprite(), AnimHandler::SHIP_IDLE, true);
    this->addChild(mainPlayer->GetSprite(), 1);
    //this->addChild(spriteNode, 1);


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
	auto enemynode = Node::create();
	enemynode->setName("eNode");
	this->addChild(enemynode, 1);

    waveSpawner = new WaveSpawner();
    waveSpawner->LoadFile("WaveData/testwave.csv");
    waveSpawner->Init();
	waveSpawner->SeteNode(enemynode);


	// cannot use same event variable for multiple objects; use CloneBy

    // Listeners
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	auto listener2 = EventListenerMouse::create();
	listener2->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	auto collisionListener = EventListenerPhysicsContact::create();
	collisionListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);

	//collisionListener->onContactPreSolve = CC_CALLBACK_1(HelloWorld::onContactPreSolve, this);
	//collisionListener->onContactPostSolve = CC_CALLBACK_3(HelloWorld::onContactPostSolve, this);
	//collisionListener->onContactSeparate = CC_CALLBACK_3(HelloWorld::onContactSeparate, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener,this);
	//schedule(CC_SCHEDULE_SELECTOR(HelloWorld::tick), 0.3f);
    // GUI
	playerGui = GUI::createPlayerGUI(mainPlayer);
	this->addChild(playerGui, 2);

    // Audio
    AudioManager::GetInstance()->PlayBackgroundMusic("Game");

    // Freeze Time Post-Processing
    timeStopped = false;
    freezeAnimationChange = false;
    screenMin.setZero();
    screenMax.set(visibleSize.width, visibleSize.height);
    xPos = yPos = 0.f;
    widthX = heightY = 0.f;

	return true;
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
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
 	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
//	bodyA->getNode()->getcom
	if (bodyA->getTag() == ENEMY && bodyB->getTag() == PLAYERPROJ)
	{
		Powerup::SetToSpawnPowerup(true);
		Powerup::SetSpawnPos(bodyA->getPosition());

		waveSpawner->DestroyEnemy(bodyA->getNode());
		bodyA->getNode()->removeFromParentAndCleanup(true);
		bodyB->getNode()->removeFromParentAndCleanup(true);

		return true;
	}
	else if (bodyB->getTag() == ENEMY &&  bodyA->getTag() == PLAYERPROJ)
	{
		Powerup::SetToSpawnPowerup(true);
		Powerup::SetSpawnPos(bodyA->getPosition());

		waveSpawner->DestroyEnemy(bodyB->getNode());
		bodyA->getNode()->removeFromParentAndCleanup(true);
		bodyB->getNode()->removeFromParentAndCleanup(true);

		return true;
	}
	else if (bodyB->getTag() == PLAYERPROJ &&  bodyA->getTag() == PLAYERPROJ)
	{
		return false;
	}
	else if (bodyA->getTag() == PLAYERPROJ &&  bodyB->getTag() == PLAYERPROJ)
	{
		return false;
	}
	else if (bodyB->getTag() == ENEMYPROJ &&  bodyA->getTag() == ENEMYPROJ)
	{
		return false;
	}
	else if (bodyB->getTag() == ENEMYPROJ &&  bodyA->getTag() == ENEMYPROJ)
	{
		return false;
	}
	else if (bodyB->getTag() == ENEMYPROJ &&  bodyA->getTag() == PLAYERPROJ)
	{
		return false;
	}
	else if (bodyA->getTag() == ENEMYPROJ &&  bodyB->getTag() == PLAYERPROJ)
	{
		return false;
	}
	else if (bodyA->getTag() == PLAYER && bodyB->getTag() == ENEMYPROJ)
	{
		bodyB->getNode()->removeFromParentAndCleanup(true);
		return true;
	}
	else if (bodyB->getTag() == PLAYER && bodyA->getTag() == ENEMYPROJ)
	{
		bodyA->getNode()->removeFromParentAndCleanup(true);
		return true;
	}
	else if (bodyA->getTag() == ENEMY && bodyB->getTag() == ENEMY)
	{
		return false;
	}
	else if (bodyB->getTag() == ENEMY && bodyA->getTag() == ENEMY)
	{
		return false;
	}
	else if (bodyA->getTag() == ENEMY && bodyB->getTag() == ENEMYPROJ)
	{
		return false;
	}
	else if (bodyB->getTag() == ENEMY && bodyA->getTag() == ENEMYPROJ)
	{
		return false;
	}
	else if (bodyA->getTag() == PLAYER && bodyB->getTag() == ENEMY)
	{
		return false;
	}
	else if (bodyB->getTag() == PLAYER && bodyA->getTag() == ENEMY)
	{
		return false;
	}
	else if (bodyA->getTag() == PLAYER && bodyB->getTag() == PLAYERPROJ)
	{
		return false;
	}
	else if (bodyB->getTag() == PLAYER && bodyA->getTag() == PLAYERPROJ)
	{ 
		return false;
	}

	// POWERUP
	else if (bodyA->getTag() == POWERUP && bodyB->getTag() == POWERUP)
	{
 		return false;
	}
	else if (bodyA->getTag() == POWERUP && bodyB->getTag() == PLAYERPROJ)
	{
		return false;
	}
	else if (bodyA->getTag() == POWERUP && bodyB->getTag() == PLAYER)
	{
		return false;
	}
	else if (bodyA->getTag() == POWERUP && bodyB->getTag() == ENEMY)
	{
		return false;
	}
	else if (bodyA->getTag() == POWERUP && bodyB->getTag() == ENEMYPROJ)
	{
		return false;
	}
	else if (bodyB->getTag() == POWERUP && bodyA->getTag() == PLAYERPROJ)
	{
		return false;
	}
	else if (bodyB->getTag() == POWERUP && bodyA->getTag() == PLAYER)
	{
		return false;
	}
	else if (bodyB->getTag() == POWERUP && bodyA->getTag() == ENEMY)
	{
		return false;
	}
	else if (bodyB->getTag() == POWERUP && bodyA->getTag() == ENEMYPROJ)
	{
		return false;
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
//bool HelloWorld::onContactSeparate(PhysicsContact& contact)
//{
//	auto bodyA = contact.getShapeA()->getBody();
//	auto bodyB = contact.getShapeB()->getBody();
//	return true;
//}
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
	if (bg_sprite1->getPositionX() <= (-bg_sprite1->getContentSize().width) + playingSize.width+3 && currbg ==0)
	{
		currbg = 1;
		bg_sprite2->setPosition(playingSize.width, -playingSize.height);
		//bg_sprite1->setPosition(playingSize.width, -playingSize.height);
	}
	if (bg_sprite2->getPositionX() <= (-bg_sprite1->getContentSize().width) + playingSize.width+3 && currbg ==1)
	{
		//bg_sprite2->setPosition(playingSize.width, -playingSize.height);
		bg_sprite1->setPosition(playingSize.width, -playingSize.height);
		currbg = 0;
	}

	// Spawn Power-up
	if (Powerup::ToSpawnPowerup())
	{
		if (Powerup::CheckSpawnPowerup())
			Powerup::RandomSpawnPowerup();

		Powerup::SetToSpawnPowerup(false);
	}

    //Input::GetInstance()->Update(dt);

    // post processing shader
    if (freezeAnimationChange) {
        UpdateFreezeAnimation(dt);
    }
    rendtex->beginWithClear(.0f, .0f, .0f, .0f);
    this->visit();
    rendtex->end();
    rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    if (timeStopped) {
        rendtexSprite->setGLProgram(proPostProcess);    // apply grayscale effect
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

void HelloWorld::FreezeTime()
{
	if (!freezeAnimationChange) {
        freezeAnimationChange = true;
		//timeStopped = !timeStopped;
        if (!timeStopped)
        {
            timeStopped = true;
            xPos = mainPlayer->GetSprite()->getPosition().x;
            yPos = mainPlayer->GetSprite()->getPosition().y;
            widthX = 0.f;
            heightY = 0.f;
        }
        else
        {
            timeStopped = false;
            //xPos = mainPlayer->GetSprite()->getPosition().x;
            //yPos = mainPlayer->GetSprite()->getPosition().y;
        }
	}
}

void HelloWorld::UpdateFreezeAnimation(float dt)
{
    float deltaChange = 600.f * dt;
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
        freezeAnimationChange = false;
}
Node* HelloWorld::getProjectileNode()
{
    return projectieNode;
}