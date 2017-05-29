#ifndef GUI_H_
#define GUI_H_

#include "cocos2d.h"
#include "Player\Player.h"
using namespace cocos2d;

class GUI :public Layer
{
private:
	//Player* player;

public:
	//GUI();
	//~GUI();
	static GUI* createPlayerGUI(Player* player); //std::string& _message);
	void initOptions( std::string& _message,Vec2 Position);
    void Update(float dt);
	//virtual bool init();


	//virtual void draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, bool transformUpdated);

	//inline virtual cocos2d::Label* getMessageLabel() { return _messageLabel; };

private:

	CREATE_FUNC(GUI);
};









#endif