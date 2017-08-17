#include "OptionsPageScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "SceneManager.h"
#include "AudioManager.h"
//#include "AnimationHandler.h"

USING_NS_CC;

Scene* OptionsPage::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = OptionsPage::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 998);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OptionsPage::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    //this->schedule(schedule_selector(HelloWorld::update), 1.0);
    this->scheduleUpdate();
	PlayerPref = UserDefault::getInstance();
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
        CC_CALLBACK_1(OptionsPage::menuCloseCallback, this));

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

    auto label = Label::createWithTTF("RAIKIRI: Lightning Cutter", "fonts/Batman.ttf", 40 * ScaleWithScreen());

    // position the label on the center of the screen
    label->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(90)));

    // add the label as a child to this layer
    this->addChild(label, 1);


    // add a label that says "Press Space to begin"
  //  auto label2 = Label::createWithTTF("Press SPACE to begin", "fonts/Batman.ttf", 24);

    // position the label on the center of the screen
    //label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
        //origin.y + visibleSize.height / 4.f + label2->getContentSize().height));

    // add the label as a child to this layer
 //   this->addChild(label2, 1);

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
    keyboardlistener->onKeyPressed = CC_CALLBACK_2(OptionsPage::onKeyPressed, this);
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(OptionsPage::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

    // Touch Listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(OptionsPage::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(OptionsPage::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	//CollideWithLabel(menu, menu);
    // Mouse Listener
    //auto listener2 = EventListenerMouse::create();
    //listener2->onMouseUp = CC_CALLBACK_1(OptionsPage::onMouseUp, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);
	

	MusicText = Label::createWithTTF("Music(On/Off)", "fonts/Batman.ttf", 50 * ScaleWithScreen());
	MusicText->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(70)));
	MusicText->setTextColor(Color4B(255, 255, 255, 255));

	GreenTickForMusic = Sprite::create("GUI/GreenTick.png");
	GreenTickForMusic->setPosition(Vec2(GetScreenWidthPercentage(70), GetScreenHeightPercentage(70)));
	GreenTickForMusic->setScale(ScaleWithScreen()*0.1f, ScaleWithScreen() * 0.1f);

	MusicToggleBox = Sprite::create("GUI/DarkBlueRectBorder.png");
	MusicToggleBox->setPosition(Vec2(GetScreenWidthPercentage(70), GetScreenHeightPercentage(70)));
	MusicToggleBox->setScale(ScaleWithScreen() *1, ScaleWithScreen() * 2);
		

	SFXText = Label::createWithTTF("SFX(On/Off)", "fonts/Batman.ttf", 50 * ScaleWithScreen());
	SFXText->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(50)));
	SFXText->setTextColor(Color4B(255, 255, 255, 255));

	GreenTickForSFX = Sprite::create("GUI/GreenTick.png");
	GreenTickForSFX->setPosition(Vec2(GetScreenWidthPercentage(70), GetScreenHeightPercentage(50)));
	GreenTickForSFX->setScale(ScaleWithScreen()*0.1f, ScaleWithScreen() * 0.1f);

	SFXToggleBox = Sprite::create("GUI/DarkBlueRectBorder.png");
	SFXToggleBox->setPosition(Vec2(GetScreenWidthPercentage(70), GetScreenHeightPercentage(50)));
	SFXToggleBox->setScale(ScaleWithScreen() * 1, ScaleWithScreen() * 2);

		
	ExitButton = Sprite::create("GUI/DarkBlueRect.png");
	ExitButton->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(20)));
	ExitButton->setScale(ScaleWithScreen() * 3, ScaleWithScreen() * 2);

	ExitText = Label::createWithTTF("Exit", "fonts/Batman.ttf", 50 * ScaleWithScreen());
	ExitText->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(20)));
	ExitText->setTextColor(Color4B(255, 255, 255, 255));

	if (PlayerPref->getStringForKey("SFX")=="")
	{
		PlayerPref->setStringForKey("SFX", "1");
		//AudioManager::GetInstance()->PlaySoundEffect()
		GreenTickForSFX->setVisible(true);
	}

	if (PlayerPref->getStringForKey("SFX") == "-1")
	{
		GreenTickForSFX->setVisible(false);
	}
	else
	{
		GreenTickForSFX->setVisible(true);
	}

	if (PlayerPref->getStringForKey("Music")=="")
	{
		PlayerPref->setStringForKey("Music", "1");
		AudioManager::GetInstance()->PlayBackgroundMusic("OptionsPage");
		GreenTickForMusic->setVisible(true);
	}

	if (PlayerPref->getStringForKey("Music") == "-1")
	{
		GreenTickForMusic->setVisible(false);
	}
	else
	{
		GreenTickForMusic->setVisible(true);
		AudioManager::GetInstance()->PlayBackgroundMusic("OptionsPage");
	}

	//StartButton->setScale(ScaleWithScreen());

	//OptionsButton = Sprite::create("GUI/DarkBlueRect.png");
	//OptionsButton->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(50)));
	//OptionsButton->setScale(ScaleWithScreen() * 3, ScaleWithScreen() * 2);

	//OptionsText = Label::createWithTTF("Options", "fonts/Batman.ttf", 50);
	//OptionsText->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(50)));
	//OptionsText->setTextColor(Color4B(0, 0, 0, 255));

	////StartText->addChild(StartButton ,2);

	this->addChild(SFXText);
	this->addChild(GreenTickForSFX,1);
	this->addChild(SFXToggleBox);
	this->addChild(MusicText, 0);
	this->addChild(GreenTickForMusic,1);
	this->addChild(MusicToggleBox);
	this->addChild(ExitButton);
	this->addChild(ExitText);
	//this->addChild(OptionsButton, -1);
	//this->addChild(OptionsText, 0);
//	this->addChild(StartText);
  

	
	//PlayerPref->setStringForKey("Test", "WEW");

    return true;
}

// Keyboard input
void OptionsPage::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_SPACE:
        SceneManager::GetInstance()->ChangeScene("HelloWorld");
        //CCDirector::getInstance()->replaceScene(
        //    TransitionFade::create(1.f, HelloWorld::createScene(), Color3B(0, 50, 50)));

        //TransitionCrossFade::create(1.5, HelloWorld::createScene()));
        break;
    }

}

void OptionsPage::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}

// Mouse input
void OptionsPage::onMouseDown(Event* event)
{
}

void OptionsPage::onMouseUp(Event* event)
{
}

bool OptionsPage::TouchCollideWithLabel(Node* NodeA, Vec3 TouchPos)
{
	return false;
}
// Touch Input
bool OptionsPage::onTouchBegan(Touch* touch, Event* event)
{
	if (ExitButton->getBoundingBox().containsPoint(touch->getLocation()))
	{
		ExitButton->setOpacity(100);
   }
//	if (AudioRect->getBoundingBox().containsPoint(touch->getLocation()))
	//{
	/*	if (PlayerPref->getStringForKey("Test") == "WEW")
			PlayerPref->setStringForKey("Test", "FUCK CUCKCUCK2DASS");
		else if (PlayerPref->getStringForKey("Test") == "FUCK CUCKCUCK2DASS")
			PlayerPref->setStringForKey("Test", "WEW");
		PlayerPref->flush();*/
	//}
    // For now, just transit scene as long as screen is tapped
   //
	
    return true;
}

void OptionsPage::onTouchEnded(Touch* touch, Event * event)
{
   
	if (ExitButton->getBoundingBox().containsPoint(touch->getLocation()))
	{
		MenuSelected = true;
	}
	ExitButton->setOpacity(255);
	if (MusicToggleBox->getBoundingBox().containsPoint(touch->getLocation()))
	{
		if (PlayerPref->getStringForKey("Music") == "-1")
		{
			PlayerPref->setStringForKey("Music", "1");
			AudioManager::GetInstance()->PlayBackgroundMusic("MainMenu",true);
			GreenTickForMusic->setVisible(true);
		}
		else
		{
			PlayerPref->setStringForKey("Music", "-1");
			AudioManager::GetInstance()->StopBackgroundMusic();
			GreenTickForMusic->setVisible(false);
		}
		PlayerPref->flush();
	}
	if (SFXToggleBox->getBoundingBox().containsPoint(touch->getLocation()))
	{
		if (PlayerPref->getStringForKey("SFX") == "-1")
		{
			PlayerPref->setStringForKey("SFX", "1");
			//SFX Audio Stuff
			GreenTickForSFX->setVisible(true);
		}
		else
		{
			PlayerPref->setStringForKey("SFX", "-1");
			//SFX Audio Stuff
			GreenTickForSFX->setVisible(false);
		}
		PlayerPref->flush();
	}
	
}

void OptionsPage::update(float dt)
{
    //Input::GetInstance()->Update(dt);
	//StartText->setString(PlayerPref->getStringForKey("Test"));
	if (MenuSelected && ExitText->getString() == "Loading")
	{
		SceneManager::GetInstance()->ChangeScene("MainMenu");
		MenuSelected = false;
	}
	if (MenuSelected)
	{
		ExitText->setString("Loading");
	}
	/*if (StartText->getString()=="Loading" &&startGame)
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
		SceneManager::GetInstance()->ChangeScene("HelloWorld");
		OptionSelected = false;
	}
	if ( OptionSelected)
	{
		OptionsText->setString("Loading");
	}*/

    // post processing shader
    //rendtex->beginWithClear(.0f, .0f, .0f, .0f);
    //this->visit();
    //rendtex->end();
    //rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
    //rendtexSprite->setGLProgram(proPostProcess);
}


void OptionsPage::menuCloseCallback(Ref* pSender)
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