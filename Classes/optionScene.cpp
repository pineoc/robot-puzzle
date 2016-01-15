#include "optionScene.h"

#include "DataSetting.h"

USING_NS_CC;
using namespace ui;

Scene* option::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
   auto layer = option::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool option::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(215, 215, 215, 255)) )
    {
        return false;
    }

	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float w = visibleSize.width / 2;
	float h = visibleSize.height / 2;

    Sprite* backgroundSprite = Sprite::create("option/option_back.jpg");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	//set key event enable
	this->setKeypadEnabled(true);

	/*back button*/
	backBtn = Button::create("option/back.png", "option/back_click.png");
	backBtn->setPosition(Vec2(120,visibleSize.height-120));
	backBtn->addTouchEventListener(CC_CALLBACK_2(option::backBtnsListener,this));
	this->addChild(backBtn);

	return true;
}

void option::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	if (EventKeyboard::KeyCode::KEY_MENU == keycode ||
		EventKeyboard::KeyCode::KEY_BACK == keycode)
	{//menu button
		Director::getInstance()->popScene();
	}
}

void option::backBtnsListener(Ref* pSender, Widget::TouchEventType type)
{
	if (Widget::TouchEventType::ENDED == type)
		Director::getInstance()->popScene();
}
void option::soundBtnsListener(Ref* pSender, Widget::TouchEventType type)
{}
void option::effectBtnsListener(Ref* pSender, Widget::TouchEventType type)
{}
void option::langBtnsListener(Ref* pSender, Widget::TouchEventType type)
{}