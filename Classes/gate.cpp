#include "gate.h"
#include "soundController.h"
#include "SimpleAudioEngine.h"

gate::gate(void)
{
}


gate::~gate(void)
{
	layoutBackGr->autorelease();
}

void gate::setImage(string letterURI)
{
	imageLetter = letterURI;
}

void gate::createBackGr()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	layoutBackGr = Layout::create();
	layoutBackGr->setAnchorPoint(Vec2());
	layoutBackGr->setPosition(Vec2());
	layoutBackGr->setSize(visibleSize);
	layoutBackGr->setBackGroundColorType(LayoutBackGroundColorType::SOLID);
	layoutBackGr->setBackGroundColor(Color3B::BLACK);
	layoutBackGr->setBackGroundColorOpacity(255 * POPUPLAYOUT_OPACITY_PERCENT);
	layoutBackGr->setZOrder(GATELAYOUT_Z);

	DelayTime* delay = DelayTime::create(5.0f);
	CallFunc* remove = CallFunc::create(CC_CALLBACK_0(gate::deleteLayout,this));
	Sequence* sequece = Sequence::create(delay, remove, NULL);

	layoutBackGr->runAction(sequece);
}

void gate::createLetter(int scene)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//letter
	spriteLetter = Sprite::create(imageLetter);
	spriteLetter->setAnchorPoint(Vec2(0.5, 1.0));
	letterPos = Vec2(visibleSize.width/2, visibleSize.height);
	spriteLetter->setPosition(letterPos);
	layoutBackGr->addChild(spriteLetter,1);
	UserDefault::getInstance()->getBoolForKey("sound");
	{ 
		soundController* sc = new soundController();
		sc->puzzleNaration(scene);
	}
}

Sprite* gate::getLetter()
{ 
	if(spriteLetter)
	{ return spriteLetter; }
	else
	{ return NULL; }
}

Layout* gate::getBackGround()
{ 
	if(layoutBackGr)
	{ return layoutBackGr; }
	else
	{ return NULL; }
}


void gate::addEvent()
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(gate::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(gate::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(gate::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(gate::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, layoutBackGr);
}

bool gate::onTouchBegan(Touch *touch, Event *unused_event) // ´êÀº ½ÃÁ¡
{ return true; }

void gate::onTouchMoved(Touch *touch, Event *unused_event) // µå·¡±×
{}

void gate::onTouchEnded(Touch *touch, Event *unused_event) // ¶¾ ½ÃÁ¡
{
	deleteLayout();
}

void gate::onTouchCancelled(Touch *touch, Event *unused_event) // ÅÍÄ¡°¡ Ãë¼ÒµÊ
{}

void gate::deleteLayout()
{
	//letter move
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo* moveUpLetter = MoveTo::create(1.0, Point(visibleSize.width/2, visibleSize.height + 600.0f));
	EaseBackIn* easeLetter = EaseBackIn::create(moveUpLetter);
	spriteLetter->runAction(easeLetter);

	//sound door open
	UserDefault::getInstance()->getBoolForKey("sound");
	{
		soundController* sc = new soundController();
		sc->doorOpen();
	}

	//touch disabled
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(layoutBackGr);
	FadeOut* fadeout = FadeOut::create(1.0);

	//remove layout
	CallFunc* remove = CallFunc::create(CC_CALLBACK_0(gate::removeLayout,this));
	Sequence* sequece = Sequence::create(fadeout, remove, NULL);

	layoutBackGr->runAction(sequece);

}

void  gate::removeLayout()
{
	layoutBackGr->removeFromParent();
}
