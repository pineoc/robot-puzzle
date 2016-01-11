#include "gate.h"


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
}

void gate::createLetter()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//letter
	spriteLetter = Sprite::create(imageLetter);
	letterPos = Vec2(visibleSize.width/2, (visibleSize.height*3)/4);
	spriteLetter->setPosition(letterPos);
	layoutBackGr->addChild(spriteLetter,1);
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
	//letter move
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo* moveLetter = MoveTo::create(2.0, Point(visibleSize.width/2, visibleSize.height + 300.0f));
	spriteLetter->runAction(moveLetter);

	//touch disabled
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(layoutBackGr);
	FadeOut* fadeout = FadeOut::create(2.0);
	layoutBackGr->runAction(fadeout);
}

void gate::onTouchCancelled(Touch *touch, Event *unused_event) // ÅÍÄ¡°¡ Ãë¼ÒµÊ
{}

void gate::deleteLayout(float t)
{
	//letter move
	Size visibleSize = Director::getInstance()->getVisibleSize();
	MoveTo* moveLetter = MoveTo::create(2.0, Point(visibleSize.width/2, visibleSize.height + 300.0f));
	spriteLetter->runAction(moveLetter);

	//touch disabled
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(layoutBackGr);
	FadeOut* fadeout = FadeOut::create(2.0);
	layoutBackGr->runAction(fadeout);
}
