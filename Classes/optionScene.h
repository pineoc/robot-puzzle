#ifndef __OPTION_H__
#define __OPTION_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class option : public cocos2d::LayerColor
{
public:
	//count puzzle
	int goalCount;


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();    

	//key touch event listener
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e);

    // implement the "static create()" method manually
    CREATE_FUNC(option);

};

#endif // __OPTION_H__
