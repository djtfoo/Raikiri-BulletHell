#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	auto sprite = Sprite::create("ZigzagGrass_Mud_Round.png");

	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(0, 0);

	float spriteWidth = sprite->getContentSize().width;
	int numOfTiles = std::ceil(visibleSize.width / spriteWidth);	// get the larger number after dividing; so there will be excess

	//nodeItems->addChild(sprite, 0);

	for (int i = 0; i < numOfTiles; ++i) {
		auto tempSprite = Sprite::create("ZigzagGrass_Mud_Round.png");
		tempSprite->setAnchorPoint(Vec2::ZERO);
		tempSprite->setPosition(i * spriteWidth, 0);
		nodeItems->addChild(tempSprite, 0);
	}

	nodeItems->setPosition(0, visibleSize.height / 2 - (visibleSize.height / 8));
	this->addChild(nodeItems, 1);

	// player sprite
	auto spriteNode = Node::create();
	spriteNode->setName("spriteNode");

	auto mainSprite = Sprite::create("Blue_Front1.png");
	mainSprite->setAnchorPoint(Vec2::ZERO);
	mainSprite->setPosition(100, visibleSize.height / 2 - (visibleSize.height / 8) + sprite->getContentSize().height);
	mainSprite->setName("mainSprite");

	spriteNode->addChild(mainSprite, 1);
	this->addChild(spriteNode, 1);

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

	// cannot use same event variable for multiple objects; use CloneBy

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		auto currSprite = this->getChildByName("spriteNode")->getChildByName("mainSprite");
		auto moveEvent = MoveBy::create(0.f, Vec2(10.f, 0.f));
		currSprite->runAction(moveEvent);
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
