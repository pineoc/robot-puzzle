#include "p2Scene.h"
#include "p3Scene.h"

//puzzle classes
#include "puzzle.h"
#include "partner.h"
#include "gameController.h"
#include "menuController.h"
#include "DataSetting.h"
#include <cstdlib>
#include <ctime>

USING_NS_CC;
using namespace ui;

Scene* secondPuzzle::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = secondPuzzle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool secondPuzzle::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	goalCount = 5;
	//rand number for arm and hand
	//num==1 : right arm, left hand
	//num==0 : left arm, right hand
	srand((unsigned int)time(NULL));
	int num = rand()%2;

	gameController::getInstance()->initPuzzleCount();
	schedule(schedule_selector(secondPuzzle::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* backgroundSprite = Sprite::create("p2/background.jpg");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	//center location
	float w = visibleSize.width/2;
	float h = visibleSize.height/2;

	menuController* myMenuController = new menuController(2);
	this->addChild(myMenuController->getMenuLayout(), 1);


	//arm puzzle
	if(num == 0)	//num==0 : left arm, right hand
	{
		//left arm puzzle
		puzzle* pz1 = new puzzle(150.0f, 150.0f, w-150.0f, h-48.0f, "p2/left_arm.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);

		//right hand puzzle
		puzzle* pz2 = new puzzle(320.0f, 150.0f, w+266.0f, h-216.0f, "p2/right_hand.png", NORMAL_PUZZLE);
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);

		
	}else{ //num==1 : right arm, left hand
		//right arm puzzle
		puzzle* pz4 = new puzzle(150.0f, 150.0f, w+162.0f, h-48.0f, "p2/right_arm.png", NORMAL_PUZZLE);
		pz4->addEvent();
		Sprite* spz4 = pz4->getPuzzle();
		Sprite* ppz4 = pz4->getPartnerPuzzle();
		this->addChild(spz4);
		this->addChild(ppz4);

		//left hand puzzle
		puzzle* pz5 = new puzzle(320.0f, 150.0f, w-249.0f, h-216.0f, "p2/left_hand.png", NORMAL_PUZZLE);
		pz5->addEvent();
		Sprite* spz5 = pz5->getPuzzle();
		Sprite* ppz5 = pz5->getPartnerPuzzle();
		this->addChild(spz5);
		this->addChild(ppz5);
	}

	//middle puzzle
	{
		puzzle* pz3 = new puzzle(510.0f, 150.0f, w+3.0f, h-357.0f, "p2/middle.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//neck puzzle
	{
		puzzle* pz6 = new puzzle(690.0f, 150.0f, w+9.0f, h+12.0f, "p2/neck.png", NORMAL_PUZZLE);
		pz6->addEvent();
		Sprite* spz6 = pz6->getPuzzle();
		Sprite* ppz6 = pz6->getPartnerPuzzle();
		this->addChild(spz6);
		this->addChild(ppz6);
	}

	//foot puzzle
	{
		puzzle* pz7 = new puzzle(888.0f, 150.0f, w+12.0f, h-551.0f, "p2/foot.png", NORMAL_PUZZLE);
		pz7->addEvent();
		Sprite* spz7 = pz7->getPuzzle();
		Sprite* ppz7 = pz7->getPartnerPuzzle(); 
		this->addChild(spz7);
		this->addChild(ppz7);
	}

	this->setKeypadEnabled(true);

    return true;
}

void secondPuzzle::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		CCLOG("Ending!");
		//unschedule check puzzle count
		this->unschedule(schedule_selector(secondPuzzle::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(secondPuzzle::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(secondPuzzle::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void secondPuzzle::showCompleteSprite(float dt){
	Sprite* spriteComplete = Sprite::create("p2/result.png");
	spriteComplete->setPosition(Vec2(543.0f, 712.0f));
	spriteComplete->setZOrder(PARTNER_Z+1);
	this->addChild(spriteComplete);
}

void secondPuzzle::showEndingPopUp(float dt){
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
	replayBtn->addTouchEventListener(CC_CALLBACK_2(secondPuzzle::endingPopupBtns, this));
	replayBtn->setTag(1);
	popLayout->addChild(replayBtn, 1);

	Button* nextBtn = Button::create("next.png", "next_s.png");
	nextBtn->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 600));
	nextBtn->addTouchEventListener(CC_CALLBACK_2(secondPuzzle::endingPopupBtns, this));
	nextBtn->setTag(2);
	popLayout->addChild(nextBtn, 1);

	Sprite* resultSpr = Sprite::create("reward.png");
	resultSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	popLayout->addChild(resultSpr, 1);
}

void secondPuzzle::endingPopupBtns(Ref* pSender, Widget::TouchEventType type){
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

void secondPuzzle::reGame(){
	Scene* s = secondPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}
void secondPuzzle::nextGame(){
	//go nextScene
	Scene* s = thirdPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}

void secondPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	if (EventKeyboard::KeyCode::KEY_MENU == keycode ||
		EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode)
	{
		nextGame();
	}
}
