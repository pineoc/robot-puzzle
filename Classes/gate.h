#ifndef __GATE_H__
#define __GATE_H__

#include "cocos2d.h"
#include <string>
#include "DataSetting.h"

using namespace std;
using namespace cocos2d;

class gate
{
public:
	//letter image
	string imageLetter;

	gate();
	~gate();
	void open(string letterURI);
	
	//get sprite
	Sprite* getLetter();

private:
	//letter sprite
	Sprite* spriteLetter;

	//positions
	Vec2 letterPos;

	//create sprite
	void createLetter();
	
};

#endif //__GATE_H__