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
	int curStage = 2;
	int score = 0;
	int totalScore = 0;
	const int LEN_X = 41; // 가로
	const int LEN_Y = 30; // 세로

public:
	std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

	static GameManager& getInstance();

	void DrawStage(Ball& ball, Bar& bar);
	void DrawStage1(Ball& ball, Bar& bar);
	void DrawStage2(Ball& ball, Bar& bar);

	void StageClear();

	int GetLENX() const;
	int GetLENY() const;

	int GetTotalScore() const;
	void CalcScore(int brokenBrickNum);
};

#endif // !G_H

