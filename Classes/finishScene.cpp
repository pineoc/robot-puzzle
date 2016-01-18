#include "finishScene.h"

//puzzle classes
#include "DataSetting.h"

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

	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* backgroundSprite = Sprite::create("finish/finish.jpg");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(0, visibleSize.height));
	backgroundSprite->setAnchorPoint(Vec2(0, 1.0));

    // add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	{
		auto act1 = EaseSineInOut::create(MoveBy::create(2.0f, Vec2(visibleSize.width - backgroundSprite->getContentSize().width, 0)));
		auto act2 = EaseSineInOut::create(MoveTo::create(2.0f, Vec2(0, visibleSize.height)));
		auto act3 = EaseSineInOut::create(MoveTo::create(1.0f, Vec2(-backgroundSprite->getContentSize().width / 3 + 100, visibleSize.height)));
		auto actS = Sequence::create(act1, act2, act3, NULL);
		backgroundSprite->runAction(actS);
	}

    return true;
}

