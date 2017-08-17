#ifndef GUI_H_
#define GUI_H_

#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;

class GUI :public Layer
{
private:
	//Player* player;

	Label* labelLives;
	Label* labelScore;
	Label* labelScoreMultiplier;
    Sprite* specialBarBackground;
    Sprite* specialBarFill;
	Sprite* ShipSprite;
	Sprite* GreenRectShip;
//	Sprite* PauseButton;
	//Sprite* GreenRectLives;
	Sprite* BlueRectScore;
	Sprite* BlueRectScoreMultiplier;

	Vec2 PlayingSize;
public:
	//GUI();
	//~GUI();
	static GUI* createPlayerGUI(Player* player); //std::string& _message);

	void initOptions(Player* player);	// generic
    void initSpecialBar();
    void Update(float dt);
	void initEndScreen(Player* player, bool win);
	//virtual bool init();
	
	void UpdateLivesLabel(const char* _message);
	void UpdateScoreLabel(int score);
	void UpdateScoreMultiplierLabel(float scoreMultiplier);
    void UpdateSpecialBarFill(float ratio);
	string ConvertScoreMultiplier(float scoreMultiplier);
	string ConvertScoreString(int score)
	{
		string scoreString = std::to_string(score);
		string temp;
		int numberOfChar = 6 - scoreString.size();
		for (int a = 0; a < numberOfChar; a++)
		{
			temp += "0";
		}
		temp += scoreString;
		return temp;
	}
	float GetScreenHeightPercentage(float percentage)
	{
		return PlayingSize.y *(percentage / 100);
	}
	float  GetScreenWidthPercentage(float percentage)
	{
		return PlayingSize.x *(percentage / 100);
	}
	const static float currentWidth;
	const static float currentHeight;
	static float ScaleWithScreen()
	{
		return (Director::getInstance()->getWinSizeInPixels().width / currentWidth);
	}
	float ScaleWithScreenWithHeight()
	{
		return (Director::getInstance()->getWinSizeInPixels().height / currentHeight);
	}
	//virtual void draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

	//inline virtual cocos2d::Label* getMessageLabel() { return _messageLabel; };

private:

	CREATE_FUNC(GUI);
};


#endif