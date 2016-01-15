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
	if (!LayerColor::initWithColor(Color4B(29,32,83,255)))
	{
		return false;
	}

	//checkFirstAppStart
	checkFirstAppStart();

	sc = new soundController();
	sc->initAudio();

	/*background image*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* backgroundSprite = Sprite::create("splash/splash1.png");

	// position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(backgroundSprite, 20);
	//action for splash
	{
		auto act0 = DelayTime::create(STARTSPLASH_DELAY_TIME);
		auto act1 = FadeOut::create(STARTSPLASH_FADEOUT_TIME);
		backgroundSprite->runAction(Sequence::createWithTwoActions(act0, act1));
	}


	monster = Sprite::create("splash/monster.png");
	monster->setAnchorPoint(Vec2(1.0, 1.0));
	monster->setPosition(Vec2(visibleSize.width + 500, visibleSize.height + 200));
	this->addChild(monster, 1);

	earth = Sprite::create("splash/earth.png");
	earth->setAnchorPoint(Vec2(0.0, 0.0));
	earth->setPosition(Vec2(-600, -600));
	this->addChild(earth, 1);

	{
		//wait for first splash
		auto act0 = DelayTime::create(STARTSPLASH_DELAY_TIME + STARTSPLASH_FADEOUT_TIME + STARTANIM_DELAY_TIME1); // 2.0f sec

		auto act1_1 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_2 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_3 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_4 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_5 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_6 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_7 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_8 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_9 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_10 = MoveBy::create(MONSTER_SHAKE_INTERVAL, Vec2(RandomHelper::random_real(-10.0, 10.0), RandomHelper::random_real(-10.0, 10.0)));
		auto act1_s = Sequence::create(act1_1, act1_2, act1_3, act1_4, act1_5, act1_6, act1_7, act1_8, act1_9, act1_10, NULL);
		auto act1 = Repeat::create(act1_s, MONSTER_SHAKE_NUM); //spend 10 sec

		//move monster
		auto act2_1 = CallFunc::create(CC_CALLBACK_0(firstSplash::moveEarth, this));
		auto act2_2 = DelayTime::create(MONSTER_MOVE_TIME);
		auto act2 = Sequence::createWithTwoActions(act2_1, act2_2);//1.8 sec
		
		//go to robotSplash
		auto act3 = DelayTime::create(STARTANIM_DELAY_TIME2); // 3.5f sec
		auto act4 = CallFunc::create(CC_CALLBACK_0(firstSplash::goSplash, this));

		//act result of monster
		auto actR = Sequence::create(act0, act1, act2, act3, act4, NULL); // 2 + 10 + 1.8 + 3.5 = 17.3

		//sound functions
		auto act_sound_delay1 = DelayTime::create(2.0);
		auto act_sound1 = CallFunc::create(CC_CALLBACK_0(firstSplash::sound1func, this));
		auto act_sound_delay2 = DelayTime::create(4.0);
		auto act_sound2 = CallFunc::create(CC_CALLBACK_0(firstSplash::sound2func, this));
		auto act_sound_delay3 = DelayTime::create(6.0);
		auto act_sound3 = CallFunc::create(CC_CALLBACK_0(firstSplash::sound3func, this));

		auto act_sound_R = Sequence::create(act_sound_delay1, act_sound1, act_sound_delay2, act_sound2, act_sound_delay3, act_sound3, NULL);

		auto actResult = Spawn::create(actR, act_sound_R, NULL);
		monster->runAction(actResult);
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

void firstSplash::moveEarth()
{
	auto act = MoveBy::create(EARTH_MOVE_TIME, Vec2(500, 500));//1.8 sec
	earth->runAction(act);

	auto act1 = MoveBy::create(MONSTER_MOVE_TIME, Vec2(1800, 0));//1.8 sec
	monster->runAction(act1);
}

void firstSplash::sound1func()
{
	sc->gameOpening(1);
}

void firstSplash::sound2func()
{
	sc->gameOpening(2);
}

void firstSplash::sound3func()
{
	sc->gameOpening(3);
}

void firstSplash::goSplash()
{
	Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, Splash::createScene());
	Director::getInstance()->replaceScene(s);
}

void firstSplash::checkFirstAppStart()
{
	UserDefault* ud = UserDefault::getInstance();
	bool firstStarted = ud->getBoolForKey("firstStart");
	if (false == firstStarted)
	{//first
		ud->setBoolForKey("firstStart", true);
		ud->setBoolForKey("kor", true);
		ud->setBoolForKey("sound", true);
		ud->flush();
	}
}
