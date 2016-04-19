#include "optionScene.h"

#include "soundController.h"
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

	//stop sound in option page
	soundController sc;
	sc.soundStop();
	sc.backgroundSoundStop();

	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float w = visibleSize.width;
	float h = visibleSize.height;


    Sprite* backgroundSprite = Sprite::create("option/option_back.jpg");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(w / 2 + origin.x, h / 2 + origin.y));

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
	soundBtn->setPosition(Vec2(3 * w / 4, h * 2 / 3));
		//add listener
	soundBtn->addTouchEventListener(CC_CALLBACK_2(option::soundBtnsListener, this));
	this->addChild(soundBtn);

	/*launguage kor/eng btn*/
	//kor button create
	langBtn_kor = Button::create("option/btn.jpg");
	//set image according to user default
	if (ud->getInstance()->getBoolForKey("kor"))
		langBtn_kor->loadTextureNormal("option/btn_s.jpg");
	else
		langBtn_kor->loadTextureNormal("option/btn.jpg");
	{
		LabelTTF* btnlabel = LabelTTF::create("한국어", "Arial", 30);
		btnlabel->setColor(Color3B::BLACK);
		btnlabel->setPosition(Vec2(langBtn_kor->getContentSize().width / 2, langBtn_kor->getContentSize().height / 2));
		langBtn_kor->addChild(btnlabel);
	}
	//set position
	langBtn_kor->setAnchorPoint(Vec2(0.5, 0.5));
	langBtn_kor->setPosition(Vec2(3 * w / 4 - 100, h * 2 / 3 + 210.0f));
	langBtn_kor->setTag(1);
	//add listener
	langBtn_kor->addTouchEventListener(CC_CALLBACK_2(option::langBtnsListener, this));
	this->addChild(langBtn_kor);

	//eng button create
	langBtn_eng = Button::create("option/btn.jpg");
	//set image according to user default
	if (ud->getInstance()->getBoolForKey("kor"))
		langBtn_eng->loadTextureNormal("option/btn.jpg");
	else
		langBtn_eng->loadTextureNormal("option/btn_s.jpg");

	{
		LabelTTF* btnlabel = LabelTTF::create("English", "Arial", 30);
		btnlabel->setColor(Color3B::BLACK);
		btnlabel->setPosition(Vec2(langBtn_eng->getContentSize().width / 2, langBtn_eng->getContentSize().height / 2));
		langBtn_eng->addChild(btnlabel);
	}

	//set position
	langBtn_eng->setAnchorPoint(Vec2(0.5, 0.5));
	langBtn_eng->setPosition(Vec2(3 * w / 4 + 100, h * 2 / 3 + 210.0f));
	langBtn_eng->setTag(2);
	//add listener
	langBtn_eng->addTouchEventListener(CC_CALLBACK_2(option::langBtnsListener, this));
	this->addChild(langBtn_eng);

	//describe label
	descLabel = LabelTTF::create("", "Arial", 35, Size::ZERO, TextHAlignment::LEFT);
	descLabel->setColor(Color3B::BLACK);
	descLabel->setPosition(Vec2(w / 2 - 50, h / 2 - 50));
	descLabel->setAnchorPoint(Vec2(0.5, 0.5));
	descLabelSetting();
	this->addChild(descLabel, 1);
	

	/*back button*/
	backBtn = Button::create("option/back.png", "option/back_s.png");
	backBtn->setPosition(Vec2(120, h - 120));
	backBtn->addTouchEventListener(CC_CALLBACK_2(option::backBtnsListener,this));
	this->addChild(backBtn);

	//set key event enable
	//this->setKeypadEnabled(true);

	return true;
}

void option::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	if (EventKeyboard::KeyCode::KEY_BACK == keycode)
	{//back button
		Director::getInstance()->popScene();
	}
}

void option::backBtnsListener(Ref* pSender, Widget::TouchEventType type)
{	// go to back
	if (Widget::TouchEventType::ENDED == type)
	{
		Director::getInstance()->popScene();
	}
		
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
		ud->flush();
	}
}


void option::langBtnsListener(Ref* pSender, Widget::TouchEventType type)
{
	ud = UserDefault::getInstance();
	if (Widget::TouchEventType::ENDED == type)
	{
		Button* button = (Button*)pSender;
		int tag = button->getTag();
		switch (tag)
		{
		case 1:
			//kor btn clicked, 
			ud->setBoolForKey("kor", true);
			button->loadTextureNormal("option/btn_s.jpg");
			langBtn_eng->loadTextureNormal("option/btn.jpg");
			break;
		case 2:
			//eng btn clicked,
			ud->setBoolForKey("kor", false);
			button->loadTextureNormal("option/btn_s.jpg");
			langBtn_kor->loadTextureNormal("option/btn.jpg");
			break;
		default:
			break;
		}
		ud->flush();
		//refresh desclabel
		descLabelSetting();
	}
}

void option::descLabelSetting()
{
	if (UserDefault::getInstance()->getBoolForKey("kor"))
	{
		std::string str = "장군로봇의 탄생의 비밀은 로봇을 좋아하는 어린이들을 위해 \n김호남 선생님이 그린 그림책, 로봇박사 테오의 두번째 이야기입니다.\n지구의 수호자, 장군로봇!\n어린이 여러분이 직접 장군로봇을 만들고 \n우주괴물로 부터 지구를 지켜주세요!";
		descLabel->setString(str);
	}
	else
	{
		std::string str = "The Secret of the birth of general Robot is\nHonam Kim\'s second story of the Dr. Robot Teo Series.\nGeneral Robot, the guardian of the Earth!\nPlease build general Robot and protect our earth \nfrom the space monster!";
		descLabel->setString(str);
	}

}
