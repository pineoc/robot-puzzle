#include "p3Scene.h"
#include "p4Scene.h"


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

	//sound stop for scene init
	soundController sc;
	sc.soundStop();

	goalCount = 3;
	gameController::getInstance()->initPuzzleCount();
	gameController::getInstance()->setIskor(UserDefault::getInstance()->getBoolForKey("kor"));
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
	
	if (UserDefault::getInstance()->getBoolForKey("kor"))
		myGate->setImage("p3_text_k.png");
	else
		myGate->setImage("p3_text_e.png");
	myGate->createLetter(3);

	myMenuController = new menuController(3);
	this->addChild(myMenuController->getMenuLayout(), 1);
	this->addChild(myMenuController->getResultLayout(), -1);

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

	//check for language change
	this->schedule(schedule_selector(thirdPuzzle::checkLanguageChange), 0.5f);

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
	//popup layout
	myMenuController->popUpResultLayout();
}

void thirdPuzzle::checkLanguageChange(float dt)
{
	if (UserDefault::getInstance()->getBoolForKey("kor") != gameController::getInstance()->getIskor())
	{
		Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, thirdPuzzle::createScene());
		Director::getInstance()->replaceScene(s);
		this->unschedule(schedule_selector(thirdPuzzle::checkLanguageChange));
	}
}

void thirdPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	
}
