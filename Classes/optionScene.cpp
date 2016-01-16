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

	/*sound on/off btn*/
	//button create
	soundBtn = Button::create("option/onoff_on.jpg", "option/onoff_off.jpg", "option/onoff_off.jpg");
		//set image according to user default
	if (ud->getInstance()->getBoolForKey("sound"))
	{ soundBtn->loadTextureNormal("option/onoff_on.jpg"); }
	else
	{ soundBtn->loadTextureNormal("option/onoff_off.jpg"); }
		//set position
	soundBtn->setAnchorPoint(Vec2(0.5, 0.5));
	soundBtn->setPosition(Vec2(3 * w / 2, h * 4 / 3));
		//add listener
	soundBtn->addTouchEventListener(CC_CALLBACK_2(option::soundBtnsListener, this));
	this->addChild(soundBtn);

	//effect on/off btn
		//button create
	effectBtn = Button::create("option/onoff_on.jpg", "option/onoff_off.jpg", "option/onoff_off.jpg");
		//set image according to user default
	if (ud->getInstance()->getBoolForKey("effect"))
	{ effectBtn->loadTextureNormal("option/onoff_on.jpg"); }
	else
	{ effectBtn->loadTextureNormal("option/onoff_off.jpg"); }
		//set position
	effectBtn->setAnchorPoint(Vec2(0.5, 0.5));
	effectBtn->setPosition(Vec2(3 * w / 2, h + 100.0f));
		//add listener
	effectBtn->addTouchEventListener(CC_CALLBACK_2(option::effectBtnsListener, this));
	this->addChild(effectBtn);

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
{	// go to back
	if (Widget::TouchEventType::ENDED == type)
		Director::getInstance()->popScene();
}

void option::soundBtnsListener(Ref* pSender, Widget::TouchEventType type)
{
	ud = UserDefault::getInstance();
	if (Widget::TouchEventType::ENDED == type)
	{
		Button* button = (Button*)pSender;
		if (ud->getBoolForKey("sound") == true)
		{	//on->off
			ud->setBoolForKey("sound", false);
			button->loadTextures("option/onoff_off.jpg", "option/onoff_off.jpg", "option/onoff_on.jpg");
		}
		else
		{	//off->on
			ud->setBoolForKey("sound", true);
			button->loadTextures("option/onoff_on.jpg", "option/onoff_on.jpg", "option/onoff_off.jpg");
		}
	}
}
void option::effectBtnsListener(Ref* pSender, Widget::TouchEventType type)
{
	ud = UserDefault::getInstance();
	if (Widget::TouchEventType::ENDED == type)
	{
		Button* button = (Button*)pSender;
		if (ud->getBoolForKey("effect") == true)
		{	//on->off
			ud->setBoolForKey("effect", false);
			button->loadTextures("option/onoff_off.jpg", "option/onoff_off.jpg", "option/onoff_on.jpg");
		}
		else
		{	//off->on
			ud->setBoolForKey("effect", true);
			button->loadTextures("option/onoff_on.jpg", "option/onoff_on.jpg", "option/onoff_off.jpg");
		}
	}

}

void option::langBtnsListener(Ref* pSender, Widget::TouchEventType type)
{}