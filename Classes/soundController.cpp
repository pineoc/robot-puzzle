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
	audio->preloadEffect("sound/correct_e1.mp3");	//good
	audio->preloadEffect("sound/correct_e2.mp3");	//good
    audio->preloadEffect("sound/correct_e3.mp3");	//good
    audio->preloadEffect("sound/correct_e4.mp3");	//good
    audio->preloadEffect("sound/correct_e5.mp3");	//good
    
    audio->preloadEffect("sound/correct_k1.mp3");	//good
    audio->preloadEffect("sound/correct_k2.mp3");	//good
    audio->preloadEffect("sound/correct_k3.mp3");	//good
    audio->preloadEffect("sound/correct_k4.mp3");	//good
    audio->preloadEffect("sound/correct_k5.mp3");	//good

	//splashScene sound
	audio->preloadEffect("sound/start_k.mp3");
	audio->preloadEffect("sound/start_e.mp3");

	//finishing
	audio->preloadBackgroundMusic("sound/ending.mp3"); //ending

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
	//auto audio = SimpleAudioEngine::getInstance();
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
	{
        //random good or excellent sound
        //TODO: file naming should change
        //-> correct_k1.mp3, correct_k2.mp3, correct_k3.mp3 ...
        int randNum = RandomHelper::random_int(1,5);
        String* file_str = String::createWithFormat("sound/correct_k%d.mp3", randNum);
        audio->playEffect(file_str->getCString());
		//RandomHelper::random_int(0,1) ? audio->playEffect("sound/good_k.mp3") : audio->playEffect("sound/excellent_k.mp3");
	}
	else
	{
        //TODO: file naming should change
        //-> correct_e1.mp3, correct_e2.mp3, correct_e3.mp3 ...
        int randNum = RandomHelper::random_int(1,5);
        String* file_str = String::createWithFormat("sound/correct_e%d.mp3", randNum);
        audio->playEffect(file_str->getCString());
		//RandomHelper::random_int(0, 1) ? audio->playEffect("sound/good_e.mp3") : audio->playEffect("sound/excellent_e.mp3");
	}
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
            //meteor effect
            audio->playEffect("sound/meteor.mp3");
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
    if (!strncmp(soundName, "monster", 7))
	{//monster sound
		SimpleAudioEngine::getInstance()->playEffect("sound/op_monster.mp3");
	}
	else if (!strncmp(soundName, "siren", 5))
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

	//ending nar
	if (UserDefault::getInstance()->getBoolForKey("kor"))
		SimpleAudioEngine::getInstance()->playEffect("sound/ending_nar_k.mp3");
	else
		SimpleAudioEngine::getInstance()->playEffect("sound/ending_nar_e.mp3");

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

void soundController::letsrock()
{
	if (UserDefault::getInstance()->getBoolForKey("sound") == false)
		return;
	if(UserDefault::getInstance()->getBoolForKey("kor"))
		SimpleAudioEngine::getInstance()->playEffect("sound/rock_and_roll_k.mp3");
	else 
		SimpleAudioEngine::getInstance()->playEffect("sound/rock_and_roll_e.mp3");
}

void soundController::soundStop()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
}

void soundController::backgroundSoundStop()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
