#ifndef __SOUNDCONTROLLER_H__
#define __SOUNDCONTROLLER_H__

#include "cocos2d.h"
#include <string>
#include "SimpleAudioEngine.h"
using namespace std;
using namespace cocos2d;

class soundController
{
private:
	//language
	bool isKorea;
public:
	//constructor
	soundController();
	~soundController();
	//init Audio
	void initAudio();
	//splashScene
	void splashSound();
	//puzzle - pick up
	void puzzlePickUp();
	//puzzle - wrong location
	void puzzleWrong();
	//puzzle - correct location
	void puzzleCorrect();
	//game opening scene
	void gameOpening(int num);
	//game ending scene
	void gameEnding();
	void gameEndingLoop(float dt);
	//puzzle opening door
	void doorOpen();
	//puzzle naration
	void puzzleNaration(int sceneNum);
	//ending pop up
	void popUp(int num);
	//sound stop
	void soundStop();
	//background sound stop
	void backgroundSoundStop();
};

#endif // __SOUNDCONTROLLER_H__
