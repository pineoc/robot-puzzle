#pragma once

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

class sixthPuzzle : public cocos2d::LayerColor
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

	//check language change
	void checkLanguageChange(float dt);

	//key event listener
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e);

    // implement the "static create()" method manually
    CREATE_FUNC(sixthPuzzle);

};
