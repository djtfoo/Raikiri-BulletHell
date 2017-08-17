#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "SceneManager.h"
#include "AudioManager.h"
//#include "AnimationHandler.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 998);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
        origin.y + closeItem->getContentSize().height / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("RAIKIRI: Lightning Cutter", "fonts/Batman.ttf", 40);

    // position the label on the center of the screen
    label->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(90)));

    // add the label as a child to this layer
    this->addChild(label, 1);


    //// add a label that says "Press Space to begin"
    //auto label2 = Label::createWithTTF("Press SPACE to begin", "fonts/Batman.ttf", 24);
	//
    //// position the label on the center of the screen
    //label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
    //    origin.y + visibleSize.height / 4.f + label2->getContentSize().height));
	//
    //// add the label as a child to this layer
    //this->addChild(label2, 1);

    // add "HelloWorld" splash screen"
  //  auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
  //  this->addChild(sprite, 0);

    proPostProcess = new GLProgram();
    proPostProcess->GLProgram::initWithFilenames("Shaders/Basic.vsh", "Shaders/ColorTransition.fsh");
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

    // Keyboard Listener
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

    // Touch Listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(MainMenu::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(MainMenu::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//CollideWithLabel(menu, menu);
    // Mouse Listener
    //auto listener2 = EventListenerMouse::create();
    //listener2->onMouseUp = CC_CALLBACK_1(MainMenu::onMouseUp, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	
    touchBegan = false;
	StartText = Label::createWithTTF("Start", "fonts/Batman.ttf", 50 * ScaleWithScreen());
	StartText->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(70)));
	StartText->setTextColor(Color4B(0, 0, 0, 255));

	StartButton = Sprite::create("GUI/DarkBlueRect.png");
	StartButton->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(70)));
	StartButton->setScale(ScaleWithScreen()*3, ScaleWithScreen() * 2);
	//StartButton->setScale(ScaleWithScreen());

	OptionsButton = Sprite::create("GUI/DarkBlueRect.png");
	OptionsButton->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(50)));
	OptionsButton->setScale(ScaleWithScreen() * 3, ScaleWithScreen() * 2);

	OptionsText = Label::createWithTTF("Options", "fonts/Batman.ttf", 50 * ScaleWithScreen());
	OptionsText->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(50)));
	OptionsText->setTextColor(Color4B(0, 0, 0, 255));

	//StartText->addChild(StartButton ,2);
	this->addChild(StartText, 0);
	this->addChild(StartButton,-1);
	this->addChild(OptionsButton, -1);
	this->addChild(OptionsText, 0);
//	this->addChild(StartText);

	// Play Audio
	if (UserDefault::getInstance()->getStringForKey("Music") == "")
	{
		UserDefault::getInstance()->setStringForKey("Music", "1");
	}

	if (UserDefault::getInstance()->getStringForKey("Music") == "1")
	{
		AudioManager::GetInstance()->PlayBackgroundMusic("MainMenu");
	}
	


	OptionSelected = false;
	startGame = false;
    return true;
}

// Keyboard input
void MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    //switch (keyCode)
    //{
    //case EventKeyboard::KeyCode::KEY_SPACE:
    //    SceneManager::GetInstance()->ChangeScene("HelloWorld");
    //    //CCDirector::getInstance()->replaceScene(
    //    //    TransitionFade::create(1.f, HelloWorld::createScene(), Color3B(0, 50, 50)));
	//
    //    //TransitionCrossFade::create(1.5, HelloWorld::createScene()));
    //    break;
    //}

}

void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}

// Mouse input
void MainMenu::onMouseDown(Event* event)
{
}

void MainMenu::onMouseUp(Event* event)
{
}

bool MainMenu::TouchCollideWithLabel(Node* NodeA, Vec3 TouchPos)
{
	return false;
}
// Touch Input
bool MainMenu::onTouchBegan(Touch* touch, Event* event)
{
    touchBegan = true;
	if (StartButton->getBoundingBox().containsPoint(touch->getLocation()))
	{
		StartButton->setOpacity(100);		
	}
	if (OptionsButton->getBoundingBox().containsPoint(touch->getLocation()))
	{
		OptionsButton->setOpacity(100);
	}
    // For now, just transit scene as long as screen is tapped
   //

    return true;
}

void MainMenu::onTouchEnded(Touch* touch, Event * event)
{
    touchBegan = false;
	if (StartButton->getBoundingBox().containsPoint(touch->getLocation()))
	{
		startGame = true;
	}
	StartButton->setOpacity(255);
	if (OptionsButton->getBoundingBox().containsPoint(touch->getLocation()))
	{
		OptionSelected = true;
	}
	OptionsButton->setOpacity(255);


	
}

void MainMenu::update(float dt)
{
    //Input::GetInstance()->Update(dt);

	if (StartText->getString()=="Loading" &&startGame)
	{
		SceneManager::GetInstance()->ChangeScene("HelloWorld");
		startGame = false;
	}
	if (startGame)
	{
		StartText->setString("Loading");
	}
	if (OptionsText->getString() == "Loading"&& OptionSelected)
	{
		SceneManager::GetInstance()->ChangeScene("OptionsPage");
		OptionSelected = false;
	}
	if ( OptionSelected)
	{
		OptionsText->setString("Loading");
	}

    // post processing shader
    //rendtex->beginWithClear(.0f, .0f, .0f, .0f);
    //this->visit();
    //rendtex->end();
    //rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    //rendtexSprite->setGLProgram(proPostProcess);
}


void MainMenu::menuCloseCallback(Ref* pSender)
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