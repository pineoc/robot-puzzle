#include "p3Scene.h"
#include "p4Scene.h"

//puzzle classes
#include "puzzle.h"
#include "partner.h"
#include "gameController.h"
#include "menuController.h"
#include "DataSetting.h"
#include "gate.h"

#include "soundController.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;

Scene* thirdPuzzle::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = thirdPuzzle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool thirdPuzzle::init()
{
    //////////////////////////////
    // 1. super init first
    if (!LayerColor::initWithColor(SCENE3_COLOR))
    {
        return false;
    }

	goalCount = 3;
	gameController::getInstance()->initPuzzleCount();
	schedule(schedule_selector(thirdPuzzle::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* robot = Sprite::create("p3/robot.png");

	// position the sprite on the center of the screen
	robot->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));

	// add the sprite as a child to this layer
	this->addChild(robot, ROBOTIMG_Z);

	//center location
	float w = visibleSize.width/2;
	float h = visibleSize.height/2;

	/*add opening gate*/
	gate* myGate = new gate();
	//back ground
	myGate->createBackGr();
	myGate->addEvent();
	this->addChild(myGate->getBackGround());
	
	myGate->setImage("p3_text.png");
	myGate->createLetter(3);

	menuController* myMenuController = new menuController(3);
	this->addChild(myMenuController->getMenuLayout(), 1);

	//box puzzle
	{
		puzzle* pz1 = new puzzle(w-170.0f, 250.0f, w+116.0f, h-84.0f, "p3/box.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}

	//b2 puzzle
	{
		puzzle* pz1 = new puzzle(w, 250.0f, w+155.0f, h-84.0f, "p3/b2.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}

	//b1 puzzle
	{
		puzzle* pz1 = new puzzle(w+170.0f, 250.0f, w+74.0f, h-84.0f, "p3/b1.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}


	this->setKeypadEnabled(true);

    return true;
}

void thirdPuzzle::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		//unschedule check puzzle count
		this->unschedule(schedule_selector(thirdPuzzle::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(thirdPuzzle::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(thirdPuzzle::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void thirdPuzzle::showCompleteSprite(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* spriteComplete = Sprite::create("p3/result.png");
	spriteComplete->setPosition(Vec2(visibleSize.width / 2 - 6.0f, visibleSize.height / 2 - 102.0f));
	spriteComplete->setZOrder(PARTNER_Z + 1);
	spriteComplete->setOpacity(0);
	this->addChild(spriteComplete);

	FadeIn* fadein = FadeIn::create(2);
	spriteComplete->runAction(fadein);

	//particle
	ParticleSystem* finishParticle = ParticleFire::create();
	finishParticle->retain();
	finishParticle->setZOrder(PARTICLE_Z);
	finishParticle->setTexture(Director::getInstance()->getTextureCache()->addImage("fire.png"));
	finishParticle->setAnchorPoint(Vec2(0.5, 0.5));
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	finishParticle->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));
	finishParticle->setScale(8);
	//finishParticle->setDuration(1.0f);
	//speed settings
	finishParticle->setSpeed(60.0f);
	finishParticle->setSpeedVar(100.0f);//speed various
	finishParticle->setLife(1.0f);
	this->addChild(finishParticle);
}

void thirdPuzzle::showEndingPopUp(float dt){
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
	replayBtn->addTouchEventListener(CC_CALLBACK_2(thirdPuzzle::endingPopupBtns, this));
	replayBtn->setTag(1);
	popLayout->addChild(replayBtn, 1);

	Button* nextBtn = Button::create("next.png", "next_s.png");
	nextBtn->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 2 - 600));
	nextBtn->addTouchEventListener(CC_CALLBACK_2(thirdPuzzle::endingPopupBtns, this));
	nextBtn->setTag(2);
	popLayout->addChild(nextBtn, 1);

	Sprite* resultSpr = Sprite::create("reward.png");
	resultSpr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	popLayout->addChild(resultSpr, 1);

	//sound
	if (UserDefault::getInstance()->getBoolForKey("sound"))
	{
		int num = cocos2d::RandomHelper::random_int(0, 1);
		soundController *sc = new soundController();
		sc->popUp(num);
	}
}

void thirdPuzzle::endingPopupBtns(Ref* pSender, Widget::TouchEventType type){
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

void thirdPuzzle::reGame(){
	Scene* s = thirdPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}
void thirdPuzzle::nextGame(){
	//go nextScene
	Scene* s = fourthPuzzle::createScene();
	Director::getInstance()->replaceScene(s);
}

void thirdPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	if (EventKeyboard::KeyCode::KEY_MENU == keycode ||
		EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keycode)
	{
		nextGame();
	}
}
