#include "partner.h"
#include "DataSetting.h"


partner::partner(Vec2 position, Size puzzleSize)
{
	//sprite create
	partnerPuzzle = Sprite::create("none.png");
	partnerPuzzle->setPosition(position);

	//set scale : partner size == puzzle size
	float x = puzzleSize.width/partnerPuzzle->getContentSize().width;
	float y = puzzleSize.height/partnerPuzzle->getContentSize().height;
	partnerPuzzle->setScaleX(x);
	partnerPuzzle->setScaleY(y);
	partnerPuzzle->setLocalZOrder(PARTNER_Z);

}


partner::~partner(void)
{
}

Sprite* partner::getPartner(){
	return partnerPuzzle;
}
