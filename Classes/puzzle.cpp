#include "puzzle.h"
#include "DataSetting.h"
#include "soundController.h"
#include "SimpleAudioEngine.h"

puzzle::puzzle(float puzzleX, float puzzleY,
	float partnerX, float partnerY, string imageURI, int puzzleType)
{
	//set corrected bit = false
	corrected = false;

	//puzzle type
	myType = puzzleType;
	//image file name set
	imageName = imageURI;

	//create spritePuzzle
	spritePuzzle = Sprite::create(imageURI);
	spriteSize = spritePuzzle->getContentSize();
	spritePuzzle->setPosition(Vec2(puzzleX, puzzleY));
	spritePuzzle->setScale(0.9f);
	spritePuzzle->setZOrder(PUZZLE_Z);//PUZZLE_Z

	createPosition = Vec2(puzzleX,puzzleY);
	//create spritePartner
	createPartner(Vec2(partnerX, partnerY));

}
puzzle::~puzzle()
{
	
}

void puzzle::createPartner(Vec2 partnerPosition)
{
	pt = new partner(partnerPosition, spriteSize);
}

Sprite* puzzle::getPuzzle(){
	return spritePuzzle;
}

Sprite* puzzle::getPartnerPuzzle(){
	return pt->getPartner();
}

//add touch event listener
void puzzle::addEvent(){
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(puzzle::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(puzzle::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(puzzle::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(puzzle::onTouchCancelled, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, spritePuzzle);
}

//compare touch location with puzzle
bool puzzle::compareLocation(Vec2 onTouchBeginLocation){
	Vec2 location = onTouchBeginLocation;
	if(puzzleRect.containsPoint(location)){ 
		spritePuzzle->setScale(1.0f);
		return true;
	}
	return false;
}

//touch start - compare
bool puzzle::onTouchBegan(Touch *touch, Event *unused_event){
	puzzleRect = spritePuzzle->getBoundingBox();
	partnerRect = utils::getCascadeBoundingBox(pt->getPartner());
	if(corrected == false){
		if(compareLocation(touch->getLocation()))
		{ touched = true; return true; }
	}
	return false;
}
//touch move(drag) - move to current touch location
void puzzle::onTouchMoved(Touch *touch, Event *unused_event){
	if(touched){
		/*run action while it picked up*/

		/*correct puzzles*/
		spritePuzzle->setPosition(touch->getLocation());
		partnerRect = pt->getPartner()->getBoundingBox();
		//CCLOG("pos : %f, %f", touch->getLocation().x, touch->getLocation().y);
		//conflict
		if(partnerRect.containsPoint(touch->getLocation())){
			//puzzle location correct
			corrected = true;
			//count correct puzzle
			gameController::getInstance()->plusPuzzleCount();
			//remove touch event listener
			Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(spritePuzzle);
			//set new&correct position
			spritePuzzle->setPosition(pt->getPartner()->getPosition());
			//change puzzle sprite if it need
			changePuzzle();
			//sound
			if(UserDefault::getInstance()->getBoolForKey("sound"))
			{
				soundController * sc = new soundController();
				sc->puzzleCorrect();
			}
			//particle
			ParticleSystem* correctParticle = ParticleExplosion::create();
			correctParticle->retain();
			correctParticle->setZOrder(PUZZLE_Z);
			correctParticle->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
			correctParticle->setAnchorPoint(Vec2(0.5, 0.5));
			correctParticle->setPosition(Vec2(spritePuzzle->getContentSize().width / 2, spritePuzzle->getContentSize().height / 2));
			correctParticle->setSpeed(100.0f);
			correctParticle->setSpeedVar(100.0f);
			correctParticle->setLife(1.0f);
			spritePuzzle->addChild(correctParticle);
		}else{
			corrected = false;
		}
	}else{
		spritePuzzle->setPosition(puzzlePosition);
	}
}
//touch end - return to created location
void puzzle::onTouchEnded(Touch *touch, Event *unused_event){
	if (false == corrected)	{
		spritePuzzle->setScale(0.9f);
		spritePuzzle->setPosition(createPosition);
		if (UserDefault::getInstance()->getBoolForKey("sound"))
		{
			soundController *sc = new soundController();
			sc->puzzleWrong();
		}
	}	
	touched = false;
}

void puzzle::onTouchCancelled(Touch *touch, Event *unused_event){
	if (false == corrected)	{
		spritePuzzle->setScale(0.9f);
		spritePuzzle->setPosition(createPosition);
		if (UserDefault::getInstance()->getBoolForKey("sound"))
		{
			soundController *sc = new soundController();
			sc->puzzleWrong();
		}
	}
	touched = false;
}

void puzzle::changePuzzle()
{
	if (CHANGE_PUZZLE == myType)
	{
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(imageName.insert(3,"result_"));
		Size textureSize = texture->getContentSize();
		Size spriteSize = spritePuzzle->getContentSize();
		spritePuzzle->setTexture(texture);
		spritePuzzle->setScaleX(textureSize.width / spriteSize.width);
		spritePuzzle->setScaleY(textureSize.height / spriteSize.height);
		spritePuzzle->setPosition(newPartnerPosition);
	}
}

void puzzle::setNewPosition(Vec2 newPosition){
	newPartnerPosition = newPosition;
}
