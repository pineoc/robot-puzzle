#ifndef __SECONDPUZZLE_H__
#define __SECONDPUZZLE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class secondPuzzle : public cocos2d::Layer
{
public:
	//count puzzle
	int goalCount;


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
    CREATE_FUNC(secondPuzzle);

};

#endif // __SECONDPUZZLE_H__
