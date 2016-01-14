#ifndef __FIRSTSPLASH_H__
#define __FIRSTSPLASH_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#define STARTSPLASH_DELAY_TIME 0.5f
#define STARTSPLASH_FADEOUT_TIME 0.3f
#define STARTANIM_DELAY_TIME1 1.2f
#define STARTANIM_MOVE_TIME 0.8f
#define STARTANIM_DELAY_TIME2 1.5f

class firstSplash : public cocos2d::Layer
{
public:

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
	void goSplash();

    // implement the "static create()" method manually
    CREATE_FUNC(firstSplash);

};

#endif // __FIRSTSPLASH_H__
