﻿#ifndef __FINISH_H__
#define __FINISH_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class finish : public cocos2d::Layer
{
private:
	cocos2d::ui::Button* goHomeBtn;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void showBtn();

	void goHomeBtnListener(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void delayedMusicStart(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(finish);

};

#endif // __FINISH_H__
