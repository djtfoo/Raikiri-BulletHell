#include "GUI.h"
#include "HelloWorldScene.h"
#include "AudioManager.h"

GUI* GUI::createPlayerGUI(Player* player)
{
	GUI* gui = new GUI();
	gui->create();
	gui->setColor(cocos2d::Color3B(0, 0, 0));

	gui->setContentSize(cocos2d::Size::Size(1, 1));
	gui->setAnchorPoint(cocos2d::Vec2(0, 0));
	//gui->initOptions(player);
	//gui->initEndScreen(player);
	gui->initOptions(player);
   gui->initSpecialBar();

	return gui;
}

void GUI::Update(float dt)
{
    //gui->initOptions("Lives Left: " + std::to_string(player->getLives()), cocos2d::Vec2(0 + 100, cocos2d::Director::getInstance()->getVisibleSize().height - 100));
}
 
void GUI::UpdateLivesLabel(const char* _message)
{
	string text = "Lives Left: ";
	text += _message;	
	labelLives->setString(text);
}

void GUI::UpdateScoreLabel(const char* _message)
{
	string text = "Score: ";
	text += _message;
	labelScore->setString(text);
}
void GUI::UpdateScoreMultiplierLabel(const char* _message)
{
	string text = "Score Multiplier: ";
	text += _message;
	labelScoreMultiplier->setString(text);
}
void GUI::initOptions(Player* player)
{
	// Lives
	labelLives = Label::createWithTTF("Lives Left: " + std::to_string(player->getLives()), "fonts/Batman.ttf", 24);
	labelLives->setColor(cocos2d::Color3B(0, 0, 0));

	addChild(labelLives, 1);

	labelLives->setPosition(cocos2d::Vec2(0 + 110, cocos2d::Director::getInstance()->getVisibleSize().height - 100));

	// Score
	labelScore = Label::createWithTTF("Score: " + std::to_string(player->getScore()), "fonts/Batman.ttf", 24);
	labelScore->setColor(cocos2d::Color3B(0, 0, 0));

	addChild(labelScore, 1);

	labelScore->setPosition(cocos2d::Vec2(0 + 100, cocos2d::Director::getInstance()->getVisibleSize().height - 150));

	labelScoreMultiplier = Label::createWithTTF("Score Multiplier: " + std::to_string(player->GetScoreMultiplier()), "fonts/Batman.ttf", 24);
	labelScoreMultiplier->setColor(cocos2d::Color3B(0, 0, 0));

	addChild(labelScoreMultiplier, 1);

	labelScoreMultiplier->setPosition(cocos2d::Vec2(0 + 100, cocos2d::Director::getInstance()->getVisibleSize().height - 200));

}
void  GUI::initEndScreen(Player* player, bool win)
{
    auto scene = Director::getInstance()->getRunningScene();
    auto layer = scene->getChildByTag(999);
    HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
    helloLayer->SetGrayscale();

    Label* endScreenLabel;
    if (win) {
        endScreenLabel = Label::createWithTTF("VICTORY! ", "fonts/Batman.ttf", 70);
    }
    else {
        endScreenLabel = Label::createWithTTF("GAME OVER ", "fonts/Batman.ttf", 70);
    }
	endScreenLabel->setColor(cocos2d::Color3B(0, 0, 0));
	Label* endScreenLabel2 = Label::createWithTTF("Press R to restart Level", "fonts/Batman.ttf", 70);
	endScreenLabel2->setColor(cocos2d::Color3B(0, 0, 0));

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Size playingSize = Size(visibleSize.width, visibleSize.height);
	endScreenLabel->setPosition(playingSize.width / 2, playingSize.height / 2);
	endScreenLabel2->setPosition(playingSize.width / 2, playingSize.height / 2-150);

    if (win) {
        labelLives->setPosition(playingSize.width / 2, playingSize.height / 2 - 50);
        labelLives->setScale(2);
    }
    else {
        labelLives->setVisible(false);
    }
    if (win) {
        labelScore->setPosition(playingSize.width / 2, playingSize.height / 2 - 100);
    }
    else {
        labelScore->setPosition(playingSize.width / 2, playingSize.height / 2 - 50);
    }
	labelScore->setScale(2);
	addChild(endScreenLabel);
	addChild(endScreenLabel2);
}
void GUI::initSpecialBar()
{
    // Size of this bar is:
    // 50 x 200 pixels
    // border is: 6 pixels wide

    // background
    specialBarBackground = Sprite::create("GUI/specialbar_background.png");

    // scale according to screen res?
    //shieldSprite->setScale(spriteSize.x / imageSize.x, spriteSize.y / imageSize.y);

    specialBarBackground->setPosition(50.f, 120.f);
    addChild(specialBarBackground, 1);

    // fill
    specialBarFill = Sprite::create("GUI/specialbar_fill.png");
    specialBarFill->setPosition(31.f, 26.f);
    specialBarFill->setAnchorPoint(Vec2::ZERO);
    specialBarFill->setScaleY(0.f);
    addChild(specialBarFill, 1);
}

void GUI::UpdateSpecialBarFill(float ratio)
{
    specialBarFill->setScaleY(ratio);
    if (ratio > 0.99f)
        AudioManager::GetInstance()->PlaySoundEffect("ChargeMax");
}


