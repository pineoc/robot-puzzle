#include "splashScene.h"
#include "p1Scene.h"

//puzzle classes
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

	/*background image*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* backgroundSprite = Sprite::create("splash/background.jpg");

	// position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	//schedule once
	this->scheduleOnce(schedule_selector(Splash::goToGame), SPLASHSCREEN_DELAYTIME);

	return true;
}

void Splash::goToGame(float dt) 
{
	//TODO: transition effect
	Scene* s = firstPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}
