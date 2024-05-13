#pragma once
#include "GameManager.h"

class Bar
{
private:
	int left;
	int right;
	int y;
	int length;
	bool isBallOnTheBar = true;
	bool isWallOnSide = false;
	GameManager& gameManager = GameManager::getInstance();
	const int LEN_X = 41; // 가로
	const int LEN_Y = 30; // 세로

public:
	Bar(int size, int middle, int yPos);

	void Init();

	int GetY();
	int GetLeft();
	int GetRight();
	int GetLength();

	bool GetIsBallOnTheBar();
	void SetIsBallOnTheBar(bool value);
	bool GetIsWallOnSide();

	void MoveLeft();
	void MoveRight();
};

