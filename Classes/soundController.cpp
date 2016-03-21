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

	//opening background
	audio->setBackgroundMusicVolume(0.5);
	//audio->preloadBackgroundMusic("sound/opening_back.wav");

	//opening
	audio->preloadEffect("sound/op1_k.mp3");
	audio->preloadEffect("sound/op2_k.mp3");
	audio->preloadEffect("sound/op3_k.mp3");
	audio->preloadEffect("sound/op1_e.mp3");
	audio->preloadEffect("sound/op2_e.mp3");
	audio->preloadEffect("sound/op3_e.mp3");
	
	//game background
	audio->preloadBackgroundMusic("sound/game_back.wav");

	//puzzle sound
	audio->preloadEffect("sound/wrong.wav");			//wrong

	//narations
	//korea narations
	audio->preloadEffect("sound/p1_n_k.mp3");	//p1Scene
	audio->preloadEffect("sound/p2_n_k.mp3");	//p2Scene
	audio->preloadEffect("sound/p3_n_k.mp3");	//p3Scene
	audio->preloadEffect("sound/p4_n_k.mp3");	//p4Scene
	audio->preloadEffect("sound/p5_n_k.mp3");	//p5Scene
	audio->preloadEffect("sound/p6_n_k.mp3");	//p6Scene
	//english narations
	audio->preloadEffect("sound/p1_n_e.mp3");	//p1Scene
	audio->preloadEffect("sound/p2_n_e.mp3");	//p2Scene
	audio->preloadEffect("sound/p3_n_e.mp3");	//p3Scene
	audio->preloadEffect("sound/p4_n_e.mp3");	//p4Scene
	audio->preloadEffect("sound/p5_n_e.mp3");	//p5Scene
	audio->preloadEffect("sound/p6_n_e.mp3");	//p6Scene

	//door open
	audio->preloadEffect("sound/door.wav"); //door open
	//end effect
	audio->preloadEffect("sound/tada.mp3");	//each game finish

	//correct eff
	audio->preloadEffect("sound/good_k.mp3");	//good
	audio->preloadEffect("sound/excellent_k.mp3");	//welldone
	audio->preloadEffect("sound/good_e.mp3");	//good
	audio->preloadEffect("sound/excellent_e.mp3");	//welldone

	//splashScene sound
	audio->preloadEffect("sound/start_k.mp3");
	audio->preloadEffect("sound/start_e.mp3");

	//finishing
	audio->preloadBackgroundMusic("sound/ending.wav"); //ending

}
void soundController::splashSound()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	//stop background sound
	backgroundSoundStop();

	if (isKorea)
		audio->playEffect("sound/start_k.mp3");
	else
		audio->playEffect("sound/start_e.mp3");
}
//puzzle - pick up
void soundController::puzzlePickUp()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	//no sound
}
//puzzle - wrong location
void soundController::puzzleWrong()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();

	audio->playEffect("sound/wrong.wav");
}
//puzzle - correct location
void soundController::puzzleCorrect()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");
	if (isKorea)
	{//random good or excellent sound
		RandomHelper::random_int(0,1) ? audio->playEffect("sound/good_k.mp3") : audio->playEffect("sound/excellent_k.mp3");
	}
	else
	{
		RandomHelper::random_int(0, 1) ? audio->playEffect("sound/good_e.mp3") : audio->playEffect("sound/excellent_e.mp3");
	}
}
//game opening scene
void soundController::gameOpening(int num)
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	//opening background sound start
	//udio->playBackgroundMusic("sound/opening_back.wav", true);

	switch (num)
	{
	case 1:
		if (isKorea)
			audio->playEffect("sound/op1_k.mp3");
		else
			audio->playEffect("sound/op1_e.mp3");
		break;
	case 2:
		if (isKorea)
			audio->playEffect("sound/op2_k.mp3");
		else
			audio->playEffect("sound/op2_e.mp3");
		break;
	case 3:
		if (isKorea)
			audio->playEffect("sound/op3_k.mp3");
		else
			audio->playEffect("sound/op3_e.mp3");
		break;
	default:
		break;
	}
	
}
void soundController::openingEffectSound(char* soundName)
{
	if (soundName == "monster")
	{//monster sound
		SimpleAudioEngine::getInstance()->playEffect("sound/op_monster.mp3");
	}
	else if (soundName == "siren")
	{//siren sound
		SimpleAudioEngine::getInstance()->playEffect("sound/op_siren.mp3");
	}
}
void soundController::startGameBackgroundSound()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("sound/game_back.wav", true);
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
	
	audio->playEffect("sound/door.wav");
}
//puzzle naration
void soundController::puzzleNaration(int sceneNum)
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	isKorea = UserDefault::getInstance()->getBoolForKey("kor");

	startGameBackgroundSound();

	switch (sceneNum)
	{
	case 1:
		if (isKorea)
			audio->playEffect("sound/p1_n_k.mp3");
		else
			audio->playEffect("sound/p1_n_e.mp3");
		break;
	case 2:
		if (isKorea)
			audio->playEffect("sound/p2_n_k.mp3");
		else
			audio->playEffect("sound/p2_n_e.mp3");
		break;
	case 3:
		if (isKorea)
			audio->playEffect("sound/p3_n_k.mp3");
		else
			audio->playEffect("sound/p3_n_e.mp3");
		break;
	case 4:
		if (isKorea)
			audio->playEffect("sound/p4_n_k.mp3");
		else
			audio->playEffect("sound/p4_n_e.mp3");
		break;
	case 5:
		if (isKorea)
			audio->playEffect("sound/p5_n_k.mp3");
		else
			audio->playEffect("sound/p5_n_e.mp3");
		break;
	case 6:
		if (isKorea)
			audio->playEffect("sound/p6_n_k.mp3");
		else
			audio->playEffect("sound/p6_n_e.mp3");
		break;
	default:
		break;
	}
}
//ending pop up
void soundController::popUp()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("sound/tada.mp3");
}

void soundController::soundStop()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void soundController::backgroundSoundStop()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
