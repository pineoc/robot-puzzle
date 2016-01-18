#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define STARTBTN_FADEIN_TIME 0.25f
#define STARTBTN_FADEOUT_TIME 1.5f

#define EYE_FADEIN_TIME 0.3f
#define EYE_FADEOUT_TIME 1.5f

#define EYE_SCALEDOWN_TIME 0.3f
#define EYE_SCALEUP_TIME 1.5f

class Splash : public cocos2d::Layer
{
public:
	//count puzzle
	int goalCount;


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	void goToGameBtnListener(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

    // implement the "static create()" method manually
    CREATE_FUNC(Splash);

};

#endif // __SPLASH_H__
