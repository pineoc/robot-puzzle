#include "gameController.h"

static gameController* instance = nullptr;

gameController::gameController(){
	initPuzzleCount();
}


gameController::~gameController(){
}

//getInstance
gameController* gameController::getInstance(){
	if(!instance){
		instance = new gameController();
	}
	return instance;
}

//count puzzle
void gameController::plusPuzzleCount(){
	cntPuzzle++;
}

int gameController::getPuzzleCount(){
	return cntPuzzle;
}

void gameController::initPuzzleCount(){
	cntPuzzle = 0;
}

void gameController::setIskor(bool kor)
{
	isKor = kor;
}

bool gameController::getIskor()
{
	return isKor;
}
