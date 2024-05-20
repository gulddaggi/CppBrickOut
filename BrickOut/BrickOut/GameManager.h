#ifndef G_H
#define G_H

#pragma once
#include <vector>

class Ball;
class Bar;

class GameManager {
private:
	GameManager() {}
	GameManager(const GameManager& ref) {}
	GameManager& operator=(const GameManager& ref) {}
	~GameManager() {}
	int curStage = 1;
	int score = 0;
	int totalScore = 0;
	int brickCount = 0;
	bool isStageClear = false;
	bool isGameClear = false;
	bool isGameOver = false;
	const int LEN_X = 28; // 가로
	const int LEN_Y = 26; // 세로

public:
	std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

	static GameManager& getInstance();

	void DrawStage(Ball& ball, Bar& bar);
	void DrawStage1(Ball& ball, Bar& bar);
	void DrawStage2(Ball& ball, Bar& bar);

	void StageClear();
	void GameClear();
	void GameOver();
	
	int GetLENX() const;
	int GetLENY() const;

	int GetTotalScore() const;
	void CalcScore(int brokenBrickNum);

	void UpdateBrickCount(int value);
	int GetBrickCount() const;

	bool GetIsStageClear() const;
	bool GetIsGameClear() const;
	bool GetIsGameOver() const;

	void Restart(Ball& ball, Bar& bar);
};

#endif // !G_H

