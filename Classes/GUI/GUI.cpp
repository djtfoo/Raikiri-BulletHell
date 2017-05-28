#include "GUI\GUI.h"

GUI* GUI::createPlayerGUI(Player* player)
{
	GUI* gui = new  GUI();
	gui->create();
	gui->setColor(cocos2d::Color3B(0, 0, 0));

	gui->setContentSize(cocos2d::Size::Size(1, 1));
	gui->setAnchorPoint(cocos2d::Vec2(0, 0));

	gui->initOptions("Lives Left: " + std::to_string(player->getLives()), cocos2d::Vec2(0+100, cocos2d::Director::getInstance()->getVisibleSize().height-100));
	gui->initOptions("Score: " + std::to_string(player->getScore()), cocos2d::Vec2(0 + 100, cocos2d::Director::getInstance()->getVisibleSize().height - 150));
	return gui;
}
void GUI::initOptions(std::string& _message, Vec2 Position)
{
	auto _messageLabel = Label::createWithTTF( _message.c_str(),"fonts/Batman.ttf", 24);
	_messageLabel->setColor(cocos2d::Color3B(255, 215, 0));

	addChild(_messageLabel, 1);

	_messageLabel->setPosition(Position);

}