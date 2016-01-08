#include "p1Scene.h"
#include "p2Scene.h"

//puzzle classes
#include "puzzle.h"
#include "partner.h"
#include "gameController.h"
#include "menuController.h"
#include "DataSetting.h"
#include "gate.h"

USING_NS_CC;
using namespace ui;

Scene* firstPuzzle::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = firstPuzzle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool firstPuzzle::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	goalCount = 6;
	gameController::getInstance()->initPuzzleCount();
	schedule(schedule_selector(firstPuzzle::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* backgroundSprite = Sprite::create("p1/background.jpg");

    // position the sprite on the center of the screen
	backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    // add the sprite as a child to this layer
	this->addChild(backgroundSprite, BACKGROUND_Z);

	//robot img sprite
/*	Sprite* robotSpr = Sprite::create("p1/robot.png");
	robotSpr->setPosition(Vec2(visibleSize.width / 2 + 5.0, visibleSize.height / 2 - 139.0));
	this->addChild(robotSpr, ROBOTIMG_Z);
*/


	//center location
	float w = visibleSize.width/2;
	float h = visibleSize.height/2;

	//add opening gate
	gate* myGate = new gate();
	myGate->open("home_s.png");
	Sprite* Sletter = myGate->getLetter();
	this->addChild(Sletter);

	//menu controller add
	menuController* myMenuController = new menuController(1);
	this->addChild(myMenuController->getMenuLayout(), 1);

	//left leg puzzle
	{
		puzzle* pz1 = new puzzle(100.0f, 150.0f, w-117.0f, h-474.0f, "p1/left_leg.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}
	
	//right leg puzzle
	{
		puzzle* pz2 = new puzzle(250.0f, 150.0f, w+128.0f, h-474.0f, "p1/right_leg.png", NORMAL_PUZZLE);
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
	}

	//middle leg puzzle
	{
		puzzle* pz3 = new puzzle(420.0f, 150.0f, w, h-330.0f, "p1/middle_leg.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//backbone puzzle
	{
		puzzle* pz3 = new puzzle(545.0f, 170.0f, w+5, h-93.0f, "p1/backbone.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//left arm puzzle
	{
		puzzle* pz3 = new puzzle(700.0f, 150.0f, w-162.0f, h-150.0f, "p1/left_arm.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//right arm puzzle
	{
		puzzle* pz3 = new puzzle(935.0f, 150.0f, w+167.0f, h-150.0f, "p1/right_arm.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//set key event enable
	this->setKeypadEnabled(true);

    return true;
}

void firstPuzzle::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		CCLOG("Ending!");
		//unschedule check puzzle count
		this->unschedule(schedule_selector(firstPuzzle::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(firstPuzzle::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(firstPuzzle::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void firstPuzzle::showCompleteSprite(float dt){
	Sprite* spriteComplete = Sprite::create("p1/result.png");
	spriteComplete->setPosition(Vec2(540.0f, 718.0f));
	spriteComplete->setZOrder(PARTNER_Z+1);
	this->addChild(spriteComplete);
}

void firstPuzzle::showEndingPopUp(float dt){
	//visible size value
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	//layout for popup
	Layout* popLayout = Layout::create();
	popLayout->setSize(visibleSize);
	popLayout->setPosition(Vec2());
	popLayout->setAnchorPoint(Vec2());
	popLayout->setBackGroundColorType(LayoutBackGroundColorType::SOLID);
	popLayout->setBackGroundColor(Color3B::BLACK);
	popLayout->setBackGroundColorOpacity(255 * POPUPLAYOUT_OPACITY_PERCENT);
	this->addChild(popLayout, POPUPLAYOUT_Z);

	//replay button
	Button* replayBtn = Button::create("replay.png", "replay_s.png");
	replayBtn->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 2 - 600));
	replayBtn->addTouchEventListener(CC_CALLBACK_2(firstPuzzle::endingPopupBtns, this));
	replayBtn->setTag(1);
	popLayout->addChild(replayBtn, 1);

	//next button
	Button* nextBtn = Button::create("next.png", "next_s.png");
	nextBtn->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 600));
	nextBtn->addTouchEventListener(CC_CALLBACK_2(firstPuzzle::endingPopupBtns, this));
	nextBtn->setTag(2);
	popLayout->addChild(nextBtn, 1);

	//result sprite of goodjob
	Sprite* resultSpr = Sprite::create("reward.png");
	resultSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	popLayout->addChild(resultSpr, 1);
}

void firstPuzzle::endingPopupBtns(Ref* pSender, Widget::TouchEventType type){
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

void firstPuzzle::reGame(){
	Scene* s = firstPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}
void firstPuzzle::nextGame(){
	//go nextScene
	Scene* s = secondPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}

void firstPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	if (EventKeyboard::KeyCode::KEY_MENU == keycode || 
		EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode)
	{//menu button
		nextGame();
	}
	if (EventKeyboard::KeyCode::KEY_BACK == keycode)
	{//back button
		Director::getInstance()->end();
	}
}
