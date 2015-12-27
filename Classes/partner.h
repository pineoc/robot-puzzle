#ifndef __PARTNER_H__
#define __PARTNER_H__

#include "cocos2d.h"
#include <string>

using namespace std;
using namespace cocos2d;

class partner
{
public:

	Sprite* partnerPuzzle;

	//constructor
	partner(Vec2 position, Size size);
	~partner(void);

	Sprite* getPartner();
};

#endif // __PARTNER_H__