#include "finishScene.h"
#include "splashScene.h"
#include "soundController.h"

#include "DataSetting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;

Scene* finish::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = finish::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool finish::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	soundController sc;
	//sc.soundStop();

	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* backgroundSprite = Sprite::create("finish/finish.png");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(0, visibleSize.height));
	backgroundSprite->setAnchorPoint(Vec2(0, 1.0));

    // add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	{
		auto delay = DelayTime::create(3.0f);
		auto act1 = EaseSineInOut::create(MoveBy::create(5.0f, Vec2(visibleSize.width - backgroundSprite->getContentSize().width, 0)));
		auto actF = CallFunc::create(CC_CALLBACK_0(finish::showBtn, this));
		auto actS = Sequence::create(delay, act1, actF, NULL);
		backgroundSprite->runAction(actS);
	}

	goHomeBtn = Button::create("finish/goHome.png", "finish/goHome_s.png");
	goHomeBtn->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	goHomeBtn->addTouchEventListener(CC_CALLBACK_2(finish::goHomeBtnListener, this));
	goHomeBtn->setTouchEnabled(false);
	goHomeBtn->setVisible(false);
	this->addChild(goHomeBtn, 3);

	{
		auto act1 = ScaleTo::create(0.3, 0.8);
		auto act2 = ScaleTo::create(1.5, 1.0);
		Sequence* actS = Sequence::createWithTwoActions(act1, act2);
		RepeatForever* actR = RepeatForever::create(actS);
		goHomeBtn->runAction(actR);
	}

	this->scheduleOnce(schedule_selector(finish::delayedMusicStart), 3.0f);

    return true;
}

void finish::showBtn()
{
	goHomeBtn->setTouchEnabled(true);
	goHomeBtn->setVisible(true);
}

void finish::goHomeBtnListener(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType type)
{
	soundController sc;
	sc.backgroundSoundStop();
	Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, Splash::createScene());
	Director::getInstance()->replaceScene(s);
}

void finish::delayedMusicStart(float dt)
{
	soundController sc;
	sc.gameEnding();
}

