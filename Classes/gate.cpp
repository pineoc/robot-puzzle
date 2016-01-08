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
	createLetter();
	Size visibleSize = Director::getInstance()->getVisibleSize();

//	spriteLetter->setOpacity(0);
	FadeOut *letterFade = FadeOut::create(2.0f);
	spriteLetter->runAction(letterFade);
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

Sprite* gate::getLetter()
{ return spriteLetter; }