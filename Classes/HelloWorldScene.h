#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class HelloWorld : public cocos2d::Layer
{
public:
	//count puzzle
	int goalCount;


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
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

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);



};

#endif // __HELLOWORLD_SCENE_H__
