#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "Input/GameInputManager.h"
#include "AnimationHandler.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
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
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));
	AnimHandler::getInstance()->Init();

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

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");
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
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	//Vector<SpriteFrame*> frames = getAnimation("ship_idle%04d.png", 15);
	auto mainSprite = Sprite::create();
	AnimHandler::getInstance()->setAnimation(mainSprite, AnimHandler::CONSTRUCT_ACTIVEP2, true);
	//auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 20);//Xseconds/Yframes (Yframes per second)
//	mainSprite->runAction(RepeatForever::create(Animate::create(animation)));

	mainSprite->setAnchorPoint(Vec2::ZERO);
	mainSprite->setPosition(100, visibleSize.height / 2 - (visibleSize.height / 8) + sprite->getContentSize().height);
	mainSprite->setName("mainSprite");

	this->addChild(spriteNode, 1);
	spriteNode->addChild(mainSprite, 1);
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



    // PLAYER
    //mainPlayer = new Player();
    //mainPlayer->Init("Blue_Front1.png", "Player", 100, 100);
    //
    //auto spriteNode = Node::create();
    //spriteNode->setName("spriteNode");
    //
    //spriteNode->addChild(mainPlayer->GetSprite(), 1);
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

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);

	auto listener2 = EventListenerMouse::create();
	listener2->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

	//auto listener2 = EventListenerKeyboard::create();


	/* COMMENT AWAYYY
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	END~~ */

	return true;
}

// Keyboard input
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    GameInputManager::GetInstance()->WhenKeyPressed(Input::EventKeyboardToKeycode(keyCode), mainPlayer);
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    GameInputManager::GetInstance()->WhenKeyReleased(Input::EventKeyboardToKeycode(keyCode), mainPlayer);
}

// Mouse input
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

    //Input::GetInstance()->Update(dt);

    // post processing shader
    rendtex->beginWithClear(.0f, .0f, .0f, .0f);
    this->visit();
    rendtex->end();
    rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    rendtexSprite->setGLProgram(proPostProcess);
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