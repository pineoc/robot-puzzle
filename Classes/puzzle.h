#ifndef __PUZZLE_H__
#define __PUZZLE_H__

#include "cocos2d.h"
#include "partner.h"
#include "gameController.h"
#include <string>

using namespace std;
using namespace cocos2d;

class puzzle
{
private:
	partner* pt;

	//puzzle Sprite
	Sprite* spritePuzzle;

	//create puzzle position
	Vec2 puzzlePosition;
	Vec2 createPosition;

	//create partner position
	Vec2 partnerPosition;

	//sprite size
	Size spriteSize;
	//touch state
	bool touched;

	//Bounding Box
	Rect puzzleRect;
	Rect partnerRect;

	//correct bit
	bool corrected;

public:
	//constructor(puzzle number, puzzle position, partner position)
    puzzle(float puzzleX, float puzzleY,
		float partnerX, float partnerY, string imageURI);

	//create partner
	void createPartner(Vec2 partnerPosition);

	//get puzzle
	Sprite* getPuzzle();
	Sprite* getPartnerPuzzle();

	void addEvent();
	//touch
	bool onTouchBegan(Touch *touch, Event *unused_event); // 닿은 시점
	void onTouchMoved(Touch *touch, Event *unused_event); // 드래그
	void onTouchEnded(Touch *touch, Event *unused_event); // 뗀 시점
	void onTouchCancelled(Touch *touch, Event *unused_event); // 터치가 취소됨
	bool compareLocation(Vec2 onTouchBeginLocation);
	~puzzle();
};

#endif // __PUZZLE_H__
