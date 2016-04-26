#ifndef __OPTION_H__
#define __OPTION_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class option : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//button funcs
	void backBtnsListener(Ref* pSender, Widget::TouchEventType type);
	void soundBtnsListener(Ref* pSender, Widget::TouchEventType type);
	void langBtnsListener(Ref* pSender, Widget::TouchEventType type);

	//label setting
	void descLabelSetting();

    // implement the "static create()" method manually
    CREATE_FUNC(option);

	//user default
	UserDefault* ud;
private:
	LabelTTF* descLabel;

	//back button
	Button* backBtn;

	//on-off buttons
	Button* soundBtn;

	//language btns
	Button* langBtn_kor;
	Button* langBtn_eng;

	
};

#endif // __OPTION_H__
