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
	RepeatForever* repeat;

	//create puzzle position
	Vec2 puzzlePosition;
	Vec2 createPosition;

	//create partner position
	Vec2 partnerPosition;
	Vec2 newPartnerPosition;

	//sprite size
	Size spriteSize;
	//touch state
	bool touched;

	//Bounding Box
	Rect puzzleRect;
	Rect partnerRect;

	//correct bit
	bool corrected;

	//puzzle type
	int myType;

	//sprite image file name
	string imageName;

public:
	//constructor(puzzle number, puzzle position, partner position)
    puzzle(float puzzleX, float puzzleY,
		float partnerX, float partnerY, string imageURI, int puzzleType);
	~puzzle();

	//create partner
	void createPartner(Vec2 partnerPosition);
	void setNewPosition(Vec2 newPosition);

	//get puzzle
	Sprite* getPuzzle();
	Sprite* getPartnerPuzzle();

	void addEvent();
	bool compareLocation(Vec2 onTouchBeginLocation);
	//touch
	bool onTouchBegan(Touch *touch, Event *unused_event); // ���� ����
	void onTouchMoved(Touch *touch, Event *unused_event); // �巡��
	void onTouchEnded(Touch *touch, Event *unused_event); // �� ����
	void onTouchCancelled(Touch *touch, Event *unused_event); // ��ġ�� ��ҵ�
	
	//change sprite puzzle function
	void changePuzzle();

};

#endif // __PUZZLE_H__
