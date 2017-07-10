#include "GUI\GUI.h"

GUI* GUI::createPlayerGUI(Player* player)
{
	GUI* gui = new GUI();
	gui->create();
	gui->setColor(cocos2d::Color3B(0, 0, 0));

	gui->setContentSize(cocos2d::Size::Size(1, 1));
	gui->setAnchorPoint(cocos2d::Vec2(0, 0));

	gui->initOptions(player);

	return gui;
}

void GUI::Update(float dt)
{
    //gui->initOptions("Lives Left: " + std::to_string(player->getLives()), cocos2d::Vec2(0 + 100, cocos2d::Director::getInstance()->getVisibleSize().height - 100));
}
 
void GUI::UpdateLivesLabel(const char* _message)
{
	labelLives->setString(_message);
}

void GUI::UpdateScoreLabel(const char* _message)
{
	labelScore->setString(_message);
}

void GUI::initOptions(Player* player)
{
	// Lives
	labelLives = Label::createWithTTF("Lives Left: " + std::to_string(player->getLives()), "fonts/Batman.ttf", 24);
	labelLives->setColor(cocos2d::Color3B(255, 215, 0));

	addChild(labelLives, 1);

	labelLives->setPosition(cocos2d::Vec2(0 + 100, cocos2d::Director::getInstance()->getVisibleSize().height - 100));

	// Score
	labelScore = Label::createWithTTF("Score: " + std::to_string(player->getScore()), "fonts/Batman.ttf", 24);
	labelScore->setColor(cocos2d::Color3B(255, 215, 0));

	addChild(labelScore, 1);

	labelScore->setPosition(cocos2d::Vec2(0 + 100, cocos2d::Director::getInstance()->getVisibleSize().height - 150));
}