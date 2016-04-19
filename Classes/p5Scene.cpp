#include "p5Scene.h"
#include "p6Scene.h"

USING_NS_CC;
using namespace ui;

Scene* fifthPuzzle::createScene()
{
    // 'scene' is an autorelease object
   auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = fifthPuzzle::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool fifthPuzzle::init()
{
    //////////////////////////////
    // 1. super init first
    if (!LayerColor::initWithColor(SCENE5_COLOR))
    {
        return false;
    }

	//sound stop for scene init
	soundController sc;
	sc.soundStop();

	goalCount = 3;
	gameController::getInstance()->initPuzzleCount();
	gameController::getInstance()->setIskor(UserDefault::getInstance()->getBoolForKey("kor"));
	schedule(schedule_selector(fifthPuzzle::checkEnding),0.5f);
    
	/*background image*/
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* robot = Sprite::create("p5/robot.png");

	// position the sprite on the center of the screen
	robot->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 250));

	// add the sprite as a child to this layer
	this->addChild(robot, ROBOTIMG_Z);

	myMenuController = new menuController(5);
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
	
	if (UserDefault::getInstance()->getBoolForKey("kor"))
		myGate->setImage("p5_text_k.png");
	else
		myGate->setImage("p5_text_e.png");
	myGate->createLetter(5);

	//left eye sprite
	{
		Sprite* eye = Sprite::create("p5/eye.png");
		eye->setPosition(Vec2(w - 156.0f, h+146.0f));
		this->addChild(eye, PUZZLE_Z);

		auto act1 = RotateBy::create(0.5f, 40.0f);
		auto act2 = act1->clone();
		auto act3 = RotateTo::create(1.0f, 0.0f);
		auto actS = Sequence::create(act1, act2, act3, NULL);
		eye->runAction(RepeatForever::create(actS));
	}

	//right eye puzzle
	{
		puzzle* eye2 = new puzzle(w-380.0f, 280.0f, w + 156.0f, h+146.0f, "p5/eye.png", NORMAL_PUZZLE);
		eye2->addEvent();
		Sprite* spz1 = eye2->getPuzzle();
		Sprite* ppz1 = eye2->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);
	}
	
	//head puzzle
	{
		puzzle* pz2 = new puzzle(w+100.0f, 400.0f, w + 12.0f, h + 305.5f, "p5/head.png", NORMAL_PUZZLE);
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);
	}

	
	//mouth puzzle
	{
		puzzle* pz3 = new puzzle(w+100.0f, 200.0f, w, h - 39.0f, "p5/mouth.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//check for language change
	this->schedule(schedule_selector(fifthPuzzle::checkLanguageChange), 0.5f);

	//this->setKeypadEnabled(true);

    return true;
}

void fifthPuzzle::checkEnding(float t){
	int curCount = gameController::getInstance()->getPuzzleCount();
	if(goalCount == curCount){
		CCLOG("Ending!");
		//unschedule check puzzle count
		this->unschedule(schedule_selector(fifthPuzzle::checkEnding));

		//ending effect
		this->scheduleOnce(schedule_selector(fifthPuzzle::showCompleteSprite), SHOWCLEARIMAGE_DELAYTIME);

		//show ending popup
		this->scheduleOnce(schedule_selector(fifthPuzzle::showEndingPopUp), SHOWPOPUPREWARD_DELAYTIME);
	}
}

//ending effect
void fifthPuzzle::showCompleteSprite(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* spriteComplete = Sprite::create("p5/result.png");
	spriteComplete->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height / 2 + 128.0f));
	spriteComplete->setLocalZOrder(PARTNER_Z + 1);
	spriteComplete->setOpacity(0);
	this->addChild(spriteComplete);

	FadeIn* fadein = FadeIn::create(2);
	spriteComplete->runAction(fadein);

	//particle
	ParticleSystem* finishParticle = ParticleFire::create();
	finishParticle->retain();
	finishParticle->setLocalZOrder(PARTICLE_Z);
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

void fifthPuzzle::showEndingPopUp(float dt){
	//popup layout
	myMenuController->popUpResultLayout();
}

void fifthPuzzle::checkLanguageChange(float dt)
{
	if (UserDefault::getInstance()->getBoolForKey("kor") != gameController::getInstance()->getIskor())
	{
		Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, fifthPuzzle::createScene());
		Director::getInstance()->replaceScene(s);
		this->unschedule(schedule_selector(fifthPuzzle::checkLanguageChange));
	}
}

void fifthPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	
}
