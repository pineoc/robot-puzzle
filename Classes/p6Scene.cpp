#include "p6Scene.h"
#include "finishScene.h"


USING_NS_CC;
using namespace ui;

Scene* sixthPuzzle::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = sixthPuzzle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool sixthPuzzle::init()
{
    //////////////////////////////
    // 1. super init first
    if (!LayerColor::initWithColor(SCENE6_COLOR))
    {
        return false;
    }

	//sound stop for scene init
	soundController sc;
	sc.soundStop();

	goalCount = 5;
	gameController::getInstance()->initPuzzleCount();
	schedule(schedule_selector(sixthPuzzle::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* robot = Sprite::create("p6/robot.png");

	// position the sprite on the center of the screen
	robot->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));

	// add the sprite as a child to this layer
	this->addChild(robot, ROBOTIMG_Z);

	myMenuController = new menuController(6);
	this->addChild(myMenuController->getMenuLayout(), 1);
	this->addChild(myMenuController->getResultLayout(), -1);

	//center location
	float w = visibleSize.width / 2;
	float h = visibleSize.height / 2;

	/*add opening gate*/
	gate* myGate = new gate();
	//back ground
	myGate->createBackGr();
	myGate->addEvent();
	this->addChild(myGate->getBackGround());
	
	myGate->setImage("p6_text.png");
	myGate->createLetter(6);
	
	//left_arm puzzle
	{
		puzzle* pz1 = new puzzle(w-405.0f, h-710.0f, w-237.0f, h-9.0f, "p6/left_arm.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}

	//right_arm puzzle
	{
		puzzle* pz2 = new puzzle(w-60.0f, h-710.0f, w+233.0f, h-9.0f, "p6/right_arm.png", NORMAL_PUZZLE);
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
	}
	
	//body puzzle
	{
		/*
		puzzle* pz2 = new puzzle(250.0f, 280.0f, w, h - 174.0f, "p6/body.png", CHANGE_PUZZLE);
		pz2->setNewPosition(Vec2(w - 15.0f, h - 175.0f));
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
		*/
		Sprite* body = Sprite::create("p6/result_body.png");
		body->setPosition(Vec2(w - 20.0f, h - 30.0f));
		this->addChild(body, 3);
	}

	//face puzzle
	{
		puzzle* pz3 = new puzzle(w-230.0f, h-590.0f, w, h + 275.0f, "p6/face.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}
	
	//head puzzle
	{
		puzzle* pz4 = new puzzle(w+270.0f, h-590.0f, w, h + 400.0f, "p6/head.png", NORMAL_PUZZLE);
		pz4->addEvent();
		Sprite* spz4 = pz4->getPuzzle();
		Sprite* ppz4 = pz4->getPartnerPuzzle();
		this->addChild(spz4);
		this->addChild(ppz4);
	}

	//leg puzzle
	{
		puzzle* pz5 = new puzzle(w+270.0f, h-825.0f, w, h - 360.0f, "p6/leg.png", NORMAL_PUZZLE);
		pz5->addEvent();
		Sprite* spz5 = pz5->getPuzzle();
		Sprite* ppz5 = pz5->getPartnerPuzzle();
		this->addChild(spz5);
		this->addChild(ppz5);
	}
	
	this->setKeypadEnabled(true);

    return true;
}

void sixthPuzzle::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		//unschedule check puzzle count
		this->unschedule(schedule_selector(sixthPuzzle::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(sixthPuzzle::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(sixthPuzzle::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void sixthPuzzle::showCompleteSprite(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* spriteComplete = Sprite::create("p6/result.png");
	spriteComplete->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 5.0f));
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

void sixthPuzzle::showEndingPopUp(float dt){
	//popup layout
	myMenuController->popUpResultLayout();
}

void sixthPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	
}
