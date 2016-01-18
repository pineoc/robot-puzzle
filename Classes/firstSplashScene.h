#ifndef __FIRSTSPLASH_H__
#define __FIRSTSPLASH_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "soundController.h"
#include "SimpleAudioEngine.h"

#define STARTSPLASH_DELAY_TIME 0.5f
#define STARTSPLASH_FADEOUT_TIME 0.3f
#define STARTANIM_DELAY_TIME1 1.2f

#define MONSTER_MOVE_TIME 1.8f
#define STARTANIM_DELAY_TIME2 3.5f

#define MONSTER_SHAKE_INTERVAL 0.2f
#define MONSTER_SHAKE_NUM 5

#define EARTH_MOVE_TIME 3.0f
#define EARTH_DELAY_TIME 3.0f
class firstSplash : public cocos2d::LayerColor
{
private:
	cocos2d::Sprite* monster;
	cocos2d::Sprite* earth;

	soundController* sc;
public:

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//move earth
	void moveEarth();
    
	//sound function for opening1 sound
	void sound1func();
	//sound function for opening2 sound
	void sound2func();
	//sound function for opening3 sound
	void sound3func();

	void goSplash();

	void skipBtnListener(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);

	void checkFirstAppStart();

    // implement the "static create()" method manually
    CREATE_FUNC(firstSplash);

};

#endif // __FIRSTSPLASH_H__
