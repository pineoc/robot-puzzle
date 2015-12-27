#pragma once
class gameController
{
public:
	gameController();
	~gameController();
	
	//sigleton instance
	

	//getInstance
	static gameController* getInstance();

	//count puzzle
	void plusPuzzleCount();
	int getPuzzleCount();
	void initPuzzleCount();

private:
	//current corrected puzzles
	int cntPuzzle;
};

