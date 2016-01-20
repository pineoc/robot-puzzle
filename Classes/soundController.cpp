#include "soundController.h"
#include "DataSetting.h"

using namespace CocosDenshion;

//constructor
soundController::soundController()
{

}
soundController::~soundController()
{}

//preload
void soundController::initAudio()
{
	auto audio = SimpleAudioEngine::getInstance();

	//opening
	audio->preloadEffect("sound/op1.mp3");
	audio->preloadEffect("sound/op2.mp3");
	audio->preloadEffect("sound/op3.mp3");
	//ending

	//puzzle sound
	audio->preloadEffect("sound/");						//pick up
	audio->preloadEffect("sound/wrong.wav");			//wrong
	audio->preloadEffect("sound/part_fix_sound.wav");	//correct
	//narations
	audio->preloadEffect("sound/p1_n.mp3");	//p1Scene
	audio->preloadEffect("sound/p2_n.mp3");	//p2Scene
	audio->preloadEffect("sound/p3_n.mp3");	//p3Scene
	audio->preloadEffect("sound/p4_n.mp3");	//p4Scene
	audio->preloadEffect("sound/p5_n.mp3");	//p5Scene
	audio->preloadEffect("sound/p6_n.mp3");	//p6Scene
	//end effect
	audio->preloadEffect("sound/");	//each game finish
	//popup
	audio->preloadEffect("sound/good_k.mp3");	//good
	audio->preloadEffect("sound/welldone_k.mp3");	//welldone
	//splashScene sound
	audio->preloadEffect("sound/start_k.mp3"); //ending1
	//finishing
	audio->preloadBackgroundMusic("sound/ending1.wav"); //ending1
	audio->preloadBackgroundMusic("sound/ending2.wav"); //ending2

}
void soundController::splashSound()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");
	if (isKorea)
		audio->playEffect("sound/start_k.mp3");
	else
		audio->playEffect("");
}
//puzzle - pick up
void soundController::puzzlePickUp()
{
}
//puzzle - wrong location
void soundController::puzzleWrong()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	audio->playEffect("sound/wrong.wav");
}
//puzzle - correct location
void soundController::puzzleCorrect()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	audio->playEffect("sound/part_fix_sound.wav");
}
//game opening scene
void soundController::gameOpening(int num)
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	switch (num)
	{
	case 1:
		if (isKorea)
			audio->playEffect("sound/op1.mp3");
		else
			audio->playEffect("sound/op1.mp3");
		break;
	case 2:
		if (isKorea)
			audio->playEffect("sound/op2.mp3");
		else
			audio->playEffect("sound/op2.mp3");
		break;
	case 3:
		if (isKorea)
			audio->playEffect("sound/op3.mp3");
		else
			audio->playEffect("sound/op3.mp3");
		break;
	default:
		break;
	}
	
}
//game ending scene
void soundController::gameEnding()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();


	audio->playBackgroundMusic("sound/ending.mp3", true);	
}

//puzzle opening door
void soundController::doorOpen()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	if (isKorea)
	{
		audio->playEffect("");
	}
	else
	{
	}
}
//puzzle naration
void soundController::puzzleNaration(int sceneNum)
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	switch (sceneNum)
	{
	case 1:
		if (isKorea)
		{
			audio->playEffect("sound/p1_n.mp3");
		}
		else
		{
		}
		break;
	case 2:
		if (isKorea)
		{
			audio->playEffect("sound/p2_n.mp3");
		}
		else
		{
		}
		break;
	case 3:
		if (isKorea)
		{
			audio->playEffect("sound/p3_n.mp3");
		}
		else
		{
		}
		break;
	case 4:
		if (isKorea)
		{
			audio->playEffect("sound/p4_n.mp3");
		}
		else
		{
		}
		break;
	case 5:
		if (isKorea)
		{
			audio->playEffect("sound/p5_n.mp3");
		}
		else
		{
		}
		break;
	case 6:
		if (isKorea)
		{
			audio->playEffect("sound/p6_n.mp3");
		}
		else
		{
		}
		break;
	default:
		break;
	}
}
//ending pop up
void soundController::popUp(int num)
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	if (isKorea)
	{
		if (num == 1)
		{
			audio->playEffect("sound/good_k.mp3");
		}
		else
		{
			audio->playEffect("sound/welldone_k.mp3");
		}

	}
	else
	{
	}
}

void soundController::soundStop()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void soundController::backgroundSoundStop()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
