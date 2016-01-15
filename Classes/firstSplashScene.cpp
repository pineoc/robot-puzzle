#include "firstSplashScene.h"
#include "splashScene.h"

//data settings header
#include "DataSetting.h"

USING_NS_CC;
using namespace ui;

Scene* firstSplash::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = firstSplash::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool firstSplash::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	/*background image*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* backgroundSprite = Sprite::create("splash/splash1.png");

	// position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(backgroundSprite, 2);
	//action for splash
	{
		auto act0 = DelayTime::create(STARTSPLASH_DELAY_TIME);
		auto act1 = FadeOut::create(STARTSPLASH_FADEOUT_TIME);
		backgroundSprite->runAction(Sequence::createWithTwoActions(act0, act1));
	}
	
	//animation sprite
	Sprite* animSpr = Sprite::create("splash/anim.jpg");
	animSpr->setAnchorPoint(Vec2());
	animSpr->setPosition(Vec2());
	this->addChild(animSpr, 1);

	{
		auto act0 = DelayTime::create(STARTSPLASH_DELAY_TIME + STARTSPLASH_FADEOUT_TIME);
		auto act1 = DelayTime::create(STARTANIM_DELAY_TIME1);
		auto act2 = MoveBy::create(STARTANIM_MOVE_TIME, Vec3(visibleSize.width - animSpr->getContentSize().width, 0, 0));
		auto act3 = DelayTime::create(STARTANIM_DELAY_TIME2);
		auto act4 = CallFunc::create(CC_CALLBACK_0(firstSplash::goSplash, this));
		animSpr->runAction(Sequence::create(act0, act1, act2, act3, act4, NULL));
	}
	
	/*
	Button* goGameBtn = Button::create("splash/start.png", "splash/start_s.png", "splash/start_s.png");
	goGameBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	goGameBtn->addTouchEventListener(CC_CALLBACK_2(firstSplash::goToGameBtnListener, this));
	this->addChild(goGameBtn, 3);

	FadeTo* act1 = FadeTo::create(STARTBTN_FADEOUT_TIME, 255 * 0.3);
	FadeIn* act2 = FadeIn::create(STARTBTN_FADEIN_TIME);
	Sequence* actS = Sequence::createWithTwoActions(act1, act2);
	RepeatForever* actR = RepeatForever::create(actS);
	goGameBtn->runAction(actR);
	*/

	return true;
}

void firstSplash::goSplash()
{
	Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, Splash::createScene());
	Director::getInstance()->replaceScene(s);
}
