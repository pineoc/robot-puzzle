#include "HelloWorldScene.h"

//puzzle classes
#include "puzzle.h"
#include "partner.h"
#include "gameController.h"
#include "DataSetting.h"

USING_NS_CC;
using namespace ui;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	goalCount = 6;
	gameController::getInstance()->initPuzzleCount();
	schedule(schedule_selector(HelloWorld::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* backgroundSprite = Sprite::create("background.jpg");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	//left leg puzzle
	{
		puzzle* pz1 = new puzzle(100.0f, 150.0f, 420.0f, 480.0f, "left_leg.png");
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}
	
	//right leg puzzle
	{
		puzzle* pz2 = new puzzle(250.0f, 150.0f, 668.0f, 486.0f, "right_leg.png");
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
	}

	//middle leg puzzle
	{
		puzzle* pz3 = new puzzle(420.0f, 150.0f, 540.0f, 630.0f, "middle_leg.png");
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//backbone puzzle
	{
		puzzle* pz3 = new puzzle(545.0f, 170.0f, 545.0f, 867.0f, "backbone.png");
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//left arm puzzle
	{
		puzzle* pz3 = new puzzle(700.0f, 150.0f, 378.0f, 810.0f, "left_arm.png");
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//right arm puzzle
	{
		puzzle* pz3 = new puzzle(935.0f, 150.0f, 707.0f, 810.0f, "right_arm.png");
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}	

    return true;
}

void HelloWorld::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		CCLOG("Ending!");
		//unschedule check puzzle count
		this->unschedule(schedule_selector(HelloWorld::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(HelloWorld::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(HelloWorld::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void HelloWorld::showCompleteSprite(float dt){
	Sprite* spriteComplete = Sprite::create("clear_body.png");
	spriteComplete->setPosition(Vec2(545.0f, 710.0f));
	spriteComplete->setZOrder(PARTNER_Z+1);
	this->addChild(spriteComplete);
}

void HelloWorld::showEndingPopUp(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//ui test
	Layout* popLayout = Layout::create();
	popLayout->setSize(visibleSize);
	popLayout->setPosition(Vec2());
	popLayout->setAnchorPoint(Vec2());
	popLayout->setBackGroundColorType(LayoutBackGroundColorType::SOLID);
	popLayout->setBackGroundColor(Color3B::BLACK);
	popLayout->setBackGroundColorOpacity(255 * POPUPLAYOUT_OPACITY_PERCENT);
	this->addChild(popLayout, POPUPLAYOUT_Z);

	Button* replayBtn = Button::create("replay.png", "replay_s.png");
	replayBtn->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2 - 600));
	replayBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::endingPopupBtns, this));
	replayBtn->setTag(1);
	popLayout->addChild(replayBtn, 1);

	Button* nextBtn = Button::create("next.png", "next_s.png");
	nextBtn->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 600));
	nextBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::endingPopupBtns, this));
	nextBtn->setTag(2);
	popLayout->addChild(nextBtn, 1);

	Sprite* resultSpr = Sprite::create("reward.png");
	resultSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	popLayout->addChild(resultSpr, 1);
}

void HelloWorld::endingPopupBtns(Ref* pSender, Widget::TouchEventType type){
	if (Widget::TouchEventType::ENDED == type){
		Button* b = (Button*)pSender;
		int tag = b->getTag();
		switch (tag)
		{
		case 1:
			reGame();
			break;
		case 2:
			nextGame();
			break;
		default:
			break;
		}
	}	
}

void HelloWorld::reGame(){
	Scene* s = HelloWorld::createScene();
	Director::getInstance()->replaceScene(s);
}
void HelloWorld::nextGame(){
	//go nextScene
	//Scene* s = nextScene::createScene();
	//Director::getInstance()->replaceScene(s);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
