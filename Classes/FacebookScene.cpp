#include "FacebookScene.h"
#include "HelloWorldScene.h"

#include "SceneManager.h"
#include "AudioManager.h"

USING_NS_CC;

Scene* FacebookScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = FacebookScene::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 996);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool FacebookScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

#ifdef SDKBOX_ENABLED
    if (!sdkbox::PluginFacebook::isLoggedIn()) {
        sdkbox::PluginFacebook::login();
    }
#endif

    //this->schedule(schedule_selector(HelloWorld::update), 1.0);
    this->scheduleUpdate();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Post to Facebook", "fonts/Batman.ttf", 32);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);


    // add a label that says "Press Space to begin"
    auto label2 = Label::createWithTTF("Press SPACE to begin", "fonts/Batman.ttf", 24);

    // position the label on the center of the screen
    label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 4.f + label2->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label2, 1);

    // Keyboard Listener
    auto keyboardlistener = EventListenerKeyboard::create();
    keyboardlistener->onKeyPressed = CC_CALLBACK_2(FacebookScene::onKeyPressed, this);
    keyboardlistener->onKeyReleased = CC_CALLBACK_2(FacebookScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardlistener, this);

    // Touch Listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(FacebookScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(FacebookScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    touchBegan = false;

    return true;
}

// Keyboard input
void FacebookScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
    case EventKeyboard::KeyCode::KEY_SPACE:
        SceneManager::GetInstance()->ChangeScene("MainMenu");
        //CCDirector::getInstance()->replaceScene(
        //    TransitionFade::create(1.f, HelloWorld::createScene(), Color3B(0, 50, 50)));

        //TransitionCrossFade::create(1.5, HelloWorld::createScene()));
        break;
    }

}

void FacebookScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{

}

// Touch Input
bool FacebookScene::onTouchBegan(Touch* touch, Event* event)
{
    touchBegan = true;

    // For now, just transit scene as long as screen is tapped
    //SceneManager::GetInstance()->ChangeScene("HelloWorld");

    return true;
}

void FacebookScene::onTouchEnded(Touch* touch, Event * event)
{
    touchBegan = false;
}

void FacebookScene::update(float dt)
{
    //Input::GetInstance()->Update(dt);
}


void FacebookScene::menuCloseCallback(Ref* pSender)
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