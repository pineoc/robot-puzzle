#include "gate.h"


gate::gate(void)
{
}


gate::~gate(void)
{
}

void gate::open(string letterURI)
{
	imageLetter = letterURI;
	createGate();
	createLetter();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	MoveBy* leftOpen = MoveBy::create(2.0, Vec2(visibleSize.width/2, 0));
	gateLeft->runAction(leftOpen);

	MoveBy* rightOpen = MoveBy::create(2.0, Vec2(-visibleSize.width/2, 0));
	gateRight->runAction(rightOpen);

//	spriteLetter->setOpacity(0);
	FadeOut *letterFade = FadeOut::create(2.0f);
	spriteLetter->runAction(letterFade);
}

void gate::createGate()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//right gate
	gateRightPos = Vec2(visibleSize.width/4, visibleSize.height/2);
	gateRight = Sprite::create("left_arrow_s.png");
	gateRight->setPosition(gateRightPos);
	gateRight->setZOrder(GATELAYOUT_Z);

	//left gate
	gateLeftPos = Vec2((visibleSize.width*3)/4, visibleSize.height/2);
	gateLeft = Sprite::create("home.png");
	gateLeft->setPosition(gateLeftPos);
	gateLeft->setZOrder(GATELAYOUT_Z);
}

void gate::createLetter()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//right gate
	letterPos = Vec2(visibleSize.width/2, (visibleSize.height*3)/4);
	spriteLetter = Sprite::create(imageLetter);
	spriteLetter->setPosition(letterPos);
	spriteLetter->setZOrder(GATELAYOUT_Z+1);
}

Sprite* gate::getRgate()
{ return gateRight; }

Sprite* gate::getLgate()
{ return gateLeft; }

Sprite* gate::getLetter()
{ return spriteLetter; }