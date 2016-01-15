#ifndef __PUZZLE_H__
#define __PUZZLE_H__

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
	//puzzle - pick up
	void puzzlePickUp();
	//puzzle - wrong location
	void puzzleWrong();
	//puzzle - correct location
	void puzzleCorrect();
	//game opening scene
	void gameOpening();
	//game ending scene
	void gameEnding();
	//puzzle opening door
	void doorOpen();
	//puzzle naration
	void puzzleNaration(int sceneNum);
	//ending pop up
	void popUp();
};

#endif // __PUZZLE_H__
