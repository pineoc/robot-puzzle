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

	//set, get iskor
	void setIskor(bool kor);
	bool getIskor();
private:
	//current corrected puzzles
	int cntPuzzle;
	bool isKor;
};

