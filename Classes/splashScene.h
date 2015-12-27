﻿#ifndef __SPLASH_H__
#define __SPLASH_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Splash : public cocos2d::Layer
{
public:
	//count puzzle
	int goalCount;


    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	void goToGame(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(Splash);

};

#endif // __SPLASH_H__
