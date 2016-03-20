#include "p2Scene.h"
#include "p3Scene.h"

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
	if (!LayerColor::initWithColor(SCENE2_COLOR))
	{
		return false;
	}

	//sound stop for scene init
	soundController sc;
	sc.soundStop();

	goalCount = 6;
	//rand number for arm and hand
	//num==1 : right arm, left hand
	//num==0 : left arm, right hand
	srand((unsigned int)time(NULL));
	int num = cocos2d::RandomHelper::random_int(0, 1);

	gameController::getInstance()->initPuzzleCount();
	gameController::getInstance()->setIskor(UserDefault::getInstance()->getBoolForKey("kor"));
	schedule(schedule_selector(secondPuzzle::checkEnding), 0.5f);

	/*background image*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* robot = Sprite::create("p2/robot.png");

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
		myGate->setImage("p2_text_k.png");
	else
		myGate->setImage("p2_text_e.png");
	myGate->createLetter(2);

	myMenuController = new menuController(2);
	this->addChild(myMenuController->getMenuLayout(), 1);
	this->addChild(myMenuController->getResultLayout(), -1);


	//arm puzzle
	if (num == 0)	//num==0 : left arm, right hand
	{
		//left arm puzzle
		puzzle* pz1 = new puzzle(w - 390.0f, 250.0f, w - 174.0f, h + 92.0f, "p2/left_arm.png", NORMAL_PUZZLE);
		pz1->addEvent();
		Sprite* spz1 = pz1->getPuzzle();
		Sprite* ppz1 = pz1->getPartnerPuzzle();
		this->addChild(spz1);
		this->addChild(ppz1);

		//right hand puzzle
		puzzle* pz2 = new puzzle(w - 220.0f, 150.0f, w + 257.0f, h - 72.0f, "p2/right_hand.png", NORMAL_PUZZLE);
		pz2->addEvent();
		Sprite* spz2 = pz2->getPuzzle();
		Sprite* ppz2 = pz2->getPartnerPuzzle();
		this->addChild(spz2);
		this->addChild(ppz2);

		//set other images
		Sprite* p1 = Sprite::create("p2/right_arm.png");
		p1->setPosition(Vec2(w + 179.0f, h + 92.0f));
		p1->setZOrder(PUZZLE_Z);
		this->addChild(p1);

		Sprite* p2 = Sprite::create("p2/left_hand.png");
		p2->setPosition(Vec2(w - 255.0f, h - 72.0f));
		p2->setZOrder(PUZZLE_Z);
		this->addChild(p2);


	}
	else { //num==1 : right arm, left hand
	//right arm puzzle
		puzzle* pz4 = new puzzle(w - 390.0f, 150.0f, w + 179.0f, h + 92.0f, "p2/right_arm.png", NORMAL_PUZZLE);
		pz4->addEvent();
		Sprite* spz4 = pz4->getPuzzle();
		Sprite* ppz4 = pz4->getPartnerPuzzle();
		this->addChild(spz4);
		this->addChild(ppz4);

		//left hand puzzle
		puzzle* pz5 = new puzzle(w - 220.0f, 250.0f, w - 255.0f, h - 72.0f, "p2/left_hand.png", NORMAL_PUZZLE);
		pz5->addEvent();
		Sprite* spz5 = pz5->getPuzzle();
		Sprite* ppz5 = pz5->getPartnerPuzzle();
		this->addChild(spz5);
		this->addChild(ppz5);

		//set other images
		Sprite* p1 = Sprite::create("p2/left_arm.png");
		p1->setPosition(Vec2(w - 174.0f, h + 92.0f));
		p1->setZOrder(PUZZLE_Z);
		this->addChild(p1);

		Sprite* p2 = Sprite::create("p2/right_hand.png");
		p2->setPosition(Vec2(w + 257.0f, h - 72.0f));
		p2->setZOrder(PUZZLE_Z);
		this->addChild(p2);
	}

	//middle puzzle
	{
		puzzle* pz3 = new puzzle(w - 30.0f, 150.0f, w - 3.0f, h - 213.0f, "p2/middle.png", NORMAL_PUZZLE);
		pz3->addEvent();
		Sprite* spz3 = pz3->getPuzzle();
		Sprite* ppz3 = pz3->getPartnerPuzzle();
		this->addChild(spz3);
		this->addChild(ppz3);
	}

	//neck puzzle
	{
		puzzle* pz6 = new puzzle(w + 150.0f, 250.0f, w + 3.0f, h + 155.0f, "p2/neck.png", NORMAL_PUZZLE);
		pz6->addEvent();
		Sprite* spz6 = pz6->getPuzzle();
		Sprite* ppz6 = pz6->getPartnerPuzzle();
		this->addChild(spz6);
		this->addChild(ppz6);
	}

	//left foot puzzle
	puzzle* pz7 = new puzzle(w + 288.0f, 150.0f, w - 120.0f, h - 405.0f, "p2/left_foot.png", NORMAL_PUZZLE);
	pz7->addEvent();
	foot1 = Sprite::create();
	foot1 = pz7->getPuzzle();
	Sprite* ppz7 = pz7->getPartnerPuzzle();
	this->addChild(foot1);
	this->addChild(ppz7);

	//right foot puzzle	
	puzzle* pz8 = new puzzle(w + 418.0f, 250.0f, w + 135.0f, h - 440.0f, "p2/right_foot.png", NORMAL_PUZZLE);
	pz8->addEvent();
	foot2 = Sprite::create();
	foot2 = pz8->getPuzzle();
	Sprite* ppz8 = pz8->getPartnerPuzzle();
	this->addChild(foot2);
	this->addChild(ppz8);

	//check for language change
	this->schedule(schedule_selector(secondPuzzle::checkLanguageChange), 0.5f);

	this->setKeypadEnabled(true);

	return true;
}

void secondPuzzle::checkEnding(float t) {
	int curCount = gameController::getInstance()->getPuzzleCount();
	if (goalCount == curCount) {
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
void secondPuzzle::showCompleteSprite(float dt) {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* spriteComplete = Sprite::create("p2/result.png");
	spriteComplete->setPosition(Vec2(visibleSize.width / 2 - 6.0f, visibleSize.height / 2 - 102.0f));
	spriteComplete->setZOrder(PARTNER_Z + 1);
	spriteComplete->setOpacity(0);
	this->addChild(spriteComplete);

	FadeIn* fadein = FadeIn::create(2);
	spriteComplete->runAction(fadein);

	FadeOut* foot1Out = FadeOut::create(2);
	foot1->runAction(foot1Out);

	FadeOut* foot2Out = FadeOut::create(2);
	foot2->runAction(foot2Out);

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


void secondPuzzle::showEndingPopUp(float dt) {
	//popup layout
	myMenuController->popUpResultLayout();
}

void secondPuzzle::checkLanguageChange(float dt)
{
	if (UserDefault::getInstance()->getBoolForKey("kor") != gameController::getInstance()->getIskor())
	{
		Scene* s = TransitionFade::create(TRANSITION_FADE_TIME, secondPuzzle::createScene());
		Director::getInstance()->replaceScene(s);
		this->unschedule(schedule_selector(secondPuzzle::checkLanguageChange));
	}
}

void secondPuzzle::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event* e)
{
	
}
