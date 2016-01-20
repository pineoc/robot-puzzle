#include "splashScene.h"
#include "p1Scene.h"

//data settings header
#include "DataSetting.h"

USING_NS_CC;
using namespace ui;

Scene* Splash::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Splash::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Splash::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//sound stop for scene init
	soundController sc;
	sc.soundStop();

	/*background image*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* backgroundSprite = Sprite::create("splash/background.jpg");

	// position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	//eye sprite
	Sprite* faceSpr = Sprite::create("splash/face.png");
	faceSpr->setAnchorPoint(Vec2(1.0, 0.0));
	faceSpr->setPosition(Vec2(visibleSize.width, visibleSize.height / 2 - 163));
	this->addChild(faceSpr, 3);

	{
		FadeTo* act1 = FadeTo::create(EYE_FADEOUT_TIME, 255 * 0.3);
		FadeIn* act2 = FadeIn::create(EYE_FADEIN_TIME);
		Sequence* actS = Sequence::createWithTwoActions(act1, act2);
		RepeatForever* actR = RepeatForever::create(actS);
		faceSpr->runAction(actR);
	}
	
	//eye sprite will have lighting effect
	

	Button* goGameBtn = Button::create("splash/start.png", "splash/start_s.png", "splash/start_s.png");
	goGameBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	goGameBtn->addTouchEventListener(CC_CALLBACK_2(Splash::goToGameBtnListener, this));
	this->addChild(goGameBtn, 3);

	{
		auto act1 = ScaleTo::create(EYE_SCALEDOWN_TIME, 0.8);
		auto act2 = ScaleTo::create(EYE_SCALEUP_TIME, 1.0);
		Sequence* actS = Sequence::createWithTwoActions(act1, act2);
		RepeatForever* actR = RepeatForever::create(actS);
		goGameBtn->runAction(actR);
	}

	sc.splashSound();

	return true;
}

void Splash::goToGameBtnListener(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
	{
		Button* btn = (Button*)pSender;
		btn->setEnabled(false);
		Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, firstPuzzle::createScene());
		Director::getInstance()->replaceScene(s);
	}
}
