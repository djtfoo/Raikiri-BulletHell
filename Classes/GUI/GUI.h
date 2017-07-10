#ifndef GUI_H_
#define GUI_H_

#include "cocos2d.h"
#include "Player\Player.h"
using namespace cocos2d;

class GUI :public Layer
{
private:
	//Player* player;

	Label* labelLives;
	Label* labelScore;

public:
	//GUI();
	//~GUI();
	static GUI* createPlayerGUI(Player* player); //std::string& _message);
	void initOptions(Player* player);	// generic
    void Update(float dt);
	//virtual bool init();

	void UpdateLivesLabel(const char* _message);
	void UpdateScoreLabel(const char* _message);

	//virtual void draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

	//inline virtual cocos2d::Label* getMessageLabel() { return _messageLabel; };

private:

	CREATE_FUNC(GUI);
};









#endif