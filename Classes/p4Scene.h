#ifndef __FOURTHPUZZLE_H__
#define __FOURTHPUZZLE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

//puzzle classes
#include "puzzle.h"
#include "partner.h"
#include "gameController.h"
#include "menuController.h"
#include "soundController.h"
#include "SimpleAudioEngine.h"
#include "DataSetting.h"
#include "gate.h"

class fourthPuzzle : public cocos2d::LayerColor
{
private:
	//count puzzle
	int goalCount;
	//menuController
	menuController* myMenuController;
public:

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	//check ending
	void checkEnding(float t);

	//ending effect
	void showCompleteSprite(float dt);
	void showEndingPopUp(float dt);

	//functions in endingPopup
	void endingPopupBtns(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	//regame
	void reGame();
	void nextGame();

	//key event listener
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e);

    // implement the "static create()" method manually
    CREATE_FUNC(fourthPuzzle);

};

#endif // __FOURTHPUZZLE_H__
