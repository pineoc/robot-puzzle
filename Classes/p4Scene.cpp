#include "p4Scene.h"
#include "p5Scene.h"


USING_NS_CC;
using namespace ui;

Scene* fourthPuzzle::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = fourthPuzzle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool fourthPuzzle::init()
{
    //////////////////////////////
    // 1. super init first
    if (!LayerColor::initWithColor(SCENE4_COLOR))
    {
        return false;
    }

	//sound stop for scene init
	soundController sc;
	sc.soundStop();

	goalCount = 5;
	gameController::getInstance()->initPuzzleCount();
	schedule(schedule_selector(fourthPuzzle::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* robot = Sprite::create("p4/robot.png");

	// position the sprite on the center of the screen
	robot->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));

	// add the sprite as a child to this layer
	this->addChild(robot, ROBOTIMG_Z);

	myMenuController = new menuController(4);
	this->addChild(myMenuController->getMenuLayout(), 1);
	this->addChild(myMenuController->getResultLayout(), -1);

	//center location
	float w = visibleSize.width/2;
	float h = visibleSize.height/2;

	/*add opening gate*/
	gate* myGate = new gate();
	//back ground
	myGate->createBackGr();
	myGate->addEvent();
	this->addChild(myGate->getBackGround());
	
	myGate->setImage("p4_text.png");
	myGate->createLetter(4);

	//left foot puzzle
	{
		puzzle* pz1 = new puzzle(w-380.0f, 280.0f, w - 129.0f, h - 438.0f, "p4/left_foot.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}

	//back puzzle
	{
		puzzle* pz2 = new puzzle(w-190.0f, 280.0f, w - 3.0f, h - 117.0f, "p4/back.png", NORMAL_PUZZLE);
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
	}

	//right_hand puzzle
	{
		puzzle* pz3 = new puzzle(w+5.0f, 280.0f, w - 174.0f, h - 153.0f, "p4/right_hand.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//right_foot puzzle
	{
		puzzle* pz3 = new puzzle(w+200.0f, 280.0f, w + 125.0f, h - 438.0f, "p4/right_foot.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//left_hand puzzle
	{
		puzzle* pz3 = new puzzle(w+380.0f, 280.0f, w + 170.0f, h -156.0f, "p4/left_hand.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	this->setKeypadEnabled(true);

    return true;
}

void fourthPuzzle::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		CCLOG("Ending!");
		//unschedule check puzzle count
		this->unschedule(schedule_selector(fourthPuzzle::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(fourthPuzzle::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(fourthPuzzle::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void fourthPuzzle::showCompleteSprite(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* spriteComplete = Sprite::create("p4/result.png");
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

void fourthPuzzle::showEndingPopUp(float dt){
	//popup layout
	myMenuController->popUpResultLayout();
}

void fourthPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	
}
