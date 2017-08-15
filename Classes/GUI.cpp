#include "GUI.h"
#include "HelloWorldScene.h"
#include "AudioManager.h"
#include <sstream>
#include <iomanip>
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

void GUI::UpdateScoreLabel(int score)
{

	string text;
	text = ConvertScoreString(score);
	labelScore->setString(text);
}
void GUI::UpdateScoreMultiplierLabel(float scoreMultiplier)
{
	string text;
	text = ConvertScoreMultiplier(scoreMultiplier);
	labelScoreMultiplier->setString(text);
}
void GUI::initOptions(Player* player)
{
	PlayingSize =  Vec2(cocos2d::Director::getInstance()->getVisibleSize().width, cocos2d::Director::getInstance()->getVisibleSize().height);
	// Lives
	labelLives = Label::createWithTTF("Lives Left: " + std::to_string(player->getLives()), "fonts/Batman.ttf", 24);
	labelLives->setColor(cocos2d::Color3B(0, 0, 0));

	addChild(labelLives, 1);

	labelLives->setPosition(cocos2d::Vec2(0 + 110, PlayingSize.y - 100));

	// Score
	labelScore = Label::createWithTTF("" + ConvertScoreString(player->getScore()), "fonts/Batman.ttf", 40);
	labelScore->setTextColor(Color4B(0, 0, 0 ,255));

	addChild(labelScore, 1);

	labelScore->setPosition(Vec2(GetScreenWidthPercentage(50), GetScreenHeightPercentage(95.75)));

	labelScoreMultiplier = Label::createWithTTF(ConvertScoreMultiplier(player->GetScoreMultiplier()), "fonts/Batman.ttf", 40);
	labelScoreMultiplier->setColor(cocos2d::Color3B(0, 0, 0));

	addChild(labelScoreMultiplier, 1);

	labelScoreMultiplier->setPosition(cocos2d::Vec2(GetScreenWidthPercentage(65), GetScreenHeightPercentage(96)));
	 
	GreenRectShip= Sprite::create("GUI/GreenRect.png");
	GreenRectShip->setPosition(cocos2d::Vec2(GetScreenWidthPercentage(11), GetScreenHeightPercentage(96)));
	GreenRectShip->setScale(2, 1.2f);

	BlueRectScore= Sprite::create("GUI/BlueRect.png");
	BlueRectScore->setPosition(GetScreenWidthPercentage(50), GetScreenHeightPercentage(96));
	BlueRectScore->setScale(2.4, 1.2f);

	BlueRectScoreMultiplier= Sprite::create("GUI/BlueRect.png");
	BlueRectScoreMultiplier->setPosition(cocos2d::Vec2(GetScreenWidthPercentage(65), GetScreenHeightPercentage(96)));
	BlueRectScoreMultiplier->setScale(0.9, 1.2f);

	addChild(GreenRectShip, -1);
	addChild(BlueRectScore, -1);
	addChild(BlueRectScoreMultiplier, -1);

}
string GUI::ConvertScoreMultiplier(float scoreMultiplier)
{
	/*	stringstream stream;
	stream << fixed << setprecision(2) << pi;
	string s = stream.str();*/
	std::stringstream stream;

	stream << std::fixed <<"x" << std::setprecision(2) <<scoreMultiplier;
	
	return stream.str();

}
void  GUI::initEndScreen(Player* player, bool win)
{
	PlayingSize = Vec2(cocos2d::Director::getInstance()->getVisibleSize().width, cocos2d::Director::getInstance()->getVisibleSize().height);
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

//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	Size playingSize = Size(visibleSize.width, visibleSize.height);
	endScreenLabel->setPosition(PlayingSize.x / 2, PlayingSize.y / 2);
	endScreenLabel2->setPosition(PlayingSize.x / 2, PlayingSize.y / 2-150);

    if (win) {
        labelLives->setPosition(PlayingSize.x / 2, PlayingSize.y / 2 - 50);
        labelLives->setScale(2);
    }
    else {
        labelLives->setVisible(false);
    }
    if (win) {
        labelScore->setPosition(PlayingSize.x / 2, PlayingSize.y / 2 - 100);
    }
    else {
        labelScore->setPosition(PlayingSize.x / 2, PlayingSize.y/ 2 - 50);
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


