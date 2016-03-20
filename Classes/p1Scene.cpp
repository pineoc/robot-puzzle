#include "p1Scene.h"
#include "p2Scene.h"



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
    if ( !LayerColor::initWithColor(SCENE1_COLOR) )
    {
        return false;
    }

	//sound stop for scene init
	soundController sc;
	sc.soundStop();

	//game controller
	goalCount = 6;
	gameController::getInstance()->initPuzzleCount();
	gameController::getInstance()->setIskor(UserDefault::getInstance()->getBoolForKey("kor"));
	schedule(schedule_selector(firstPuzzle::checkEnding), 0.5f);
    	
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* robot = Sprite::create("p1/robot.png");

    // position the sprite on the center of the screen
	robot->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));

    // add the sprite as a child to this layer
	this->addChild(robot, ROBOTIMG_Z);

	//center location
	float w = visibleSize.width / 2;
	float h = visibleSize.height / 2;

	/*add opening gate*/
	gate* myGate = new gate();
	//back ground
	myGate->createBackGr();
	myGate->addEvent();
	this->addChild(myGate->getBackGround());
	
	if (UserDefault::getInstance()->getBoolForKey("kor"))
		myGate->setImage("p1_text_k.png");
	else
		myGate->setImage("p1_text_e.png");
	myGate->createLetter(1);

	//menu controller add
	myMenuController = new menuController(1);
	this->addChild(myMenuController->getMenuLayout(), 1);
	this->addChild(myMenuController->getResultLayout(), -1);

	//left leg puzzle
	{
		puzzle* pz1 = new puzzle(w-450.0f, 250.0f, w-126.0f, h-336.0f, "p1/left_leg.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}
	
	//right leg puzzle
	{
		puzzle* pz2 = new puzzle(w-310.0f, 250.0f, w+128.0f, h-336.0f, "p1/right_leg.png", NORMAL_PUZZLE);
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
	}

	//middle leg puzzle
	{
		puzzle* pz3 = new puzzle(w-140.0f, 250.0f, w, h-192.0f, "p1/middle_leg.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//backbone puzzle
	{
		puzzle* pz3 = new puzzle(w, 250.0f, w+3, h+51.0f, "p1/backbone.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//left arm puzzle
	{
		puzzle* pz3 = new puzzle(w+160.0f, 200.0f, w-168.0f, h-15.0f, "p1/left_arm.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//right arm puzzle 
	{
		puzzle* pz3 = new puzzle(w+395.0f, 300.0f, w+167.0f, h-15.0f, "p1/right_arm.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//check for language change
	this->schedule(schedule_selector(firstPuzzle::checkLanguageChange), 0.5f);

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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* spriteComplete = Sprite::create("p1/result.png");
	spriteComplete->setPosition(Vec2(visibleSize.width / 2-3.0f, visibleSize.height / 2 -102.0f));
	spriteComplete->setZOrder(COMPLETE_Z);
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

void firstPuzzle::showEndingPopUp(float dt){
	//popup layout
	myMenuController->popUpResultLayout();
}

void firstPuzzle::checkLanguageChange(float dt)
{
	if (UserDefault::getInstance()->getBoolForKey("kor") != gameController::getInstance()->getIskor())
	{
		Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, firstPuzzle::createScene());
		Director::getInstance()->replaceScene(s);
		this->unschedule(schedule_selector(firstPuzzle::checkLanguageChange));
	}
}

void firstPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	
}
