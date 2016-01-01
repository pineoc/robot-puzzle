#include "p7Scene.h"
#include "finishScene.h"

//puzzle classes
#include "puzzle.h"
#include "partner.h"
#include "gameController.h"
#include "menuController.h"
#include "DataSetting.h"

USING_NS_CC;
using namespace ui;

Scene* seventhPuzzle::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = seventhPuzzle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool seventhPuzzle::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	goalCount = 5;
	gameController::getInstance()->initPuzzleCount();
	//game ending check
	schedule(schedule_selector(seventhPuzzle::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* backgroundSprite = Sprite::create("p7/background.jpg");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	menuController* myMenuController = new menuController(7);
	this->addChild(myMenuController->getMenuLayout(), 1);

	
	//arm puzzle
	{
		puzzle* pz1 = new puzzle(100.0f, 150.0f, 420.0f, 480.0f, "p7/arm.png");
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		spz1->setTexture(Director::getInstance()->getTextureCache()->addImage("p7/body.png"));
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}
	
	//body puzzle
	{
		puzzle* pz2 = new puzzle(250.0f, 150.0f, 668.0f, 486.0f, "p7/body.png");
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
	}

	//face puzzle
	{
		puzzle* pz3 = new puzzle(420.0f, 150.0f, 540.0f, 630.0f, "p7/face.png");
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//head puzzle
	{
		puzzle* pz4 = new puzzle(545.0f, 170.0f, 545.0f, 867.0f, "p7/head.png");
		pz4->addEvent();
		Sprite* spz4 = pz4->getPuzzle();
		Sprite* ppz4 = pz4->getPartnerPuzzle();
		this->addChild(spz4);
		this->addChild(ppz4);
	}

	//leg puzzle
	{
		puzzle* pz5 = new puzzle(700.0f, 150.0f, 378.0f, 810.0f, "p7/leg.png");
		pz5->addEvent();
		Sprite* spz5 = pz5->getPuzzle();
		Sprite* ppz5 = pz5->getPartnerPuzzle();
		this->addChild(spz5);
		this->addChild(ppz5);
	}
	
	//set back key enable
	this->setKeypadEnabled(true);

    return true;
}

void seventhPuzzle::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		CCLOG("Ending!");
		//unschedule check puzzle count
		this->unschedule(schedule_selector(seventhPuzzle::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(seventhPuzzle::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(seventhPuzzle::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void seventhPuzzle::showCompleteSprite(float dt){
	Sprite* spriteComplete = Sprite::create("p7/result.png");
	spriteComplete->setPosition(Vec2(545.0f, 710.0f));
	spriteComplete->setZOrder(PARTNER_Z+1);
	this->addChild(spriteComplete);
}

void seventhPuzzle::showEndingPopUp(float dt){
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
	replayBtn->addTouchEventListener(CC_CALLBACK_2(seventhPuzzle::endingPopupBtns, this));
	replayBtn->setTag(1);
	popLayout->addChild(replayBtn, 1);

	Button* nextBtn = Button::create("next.png", "next_s.png");
	nextBtn->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 600));
	nextBtn->addTouchEventListener(CC_CALLBACK_2(seventhPuzzle::endingPopupBtns, this));
	nextBtn->setTag(2);
	popLayout->addChild(nextBtn, 1);

	Sprite* resultSpr = Sprite::create("reward.png");
	resultSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	popLayout->addChild(resultSpr, 1);
}

void seventhPuzzle::endingPopupBtns(Ref* pSender, Widget::TouchEventType type){
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

void seventhPuzzle::reGame(){
	Scene* s = seventhPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}
void seventhPuzzle::nextGame(){
	//go nextScene, finish
	Scene* s = finish::createScene();
	Director::getInstance()->replaceScene(s);
}

void seventhPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	if (EventKeyboard::KeyCode::KEY_MENU == keycode ||
		EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode)
	{
		nextGame();
	}
}
