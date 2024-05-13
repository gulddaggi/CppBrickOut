#pragma once
#include <vector>
#include "GameManager.h"

class Ball
{
public:
	enum class Direction
	{
		UPRIGHT,
		UPLEFT,
		DOWNRIGHT,
		DOWNLEFT
	};

private:
	int x;
	int y;
	bool isBallMoving;
	int originX;
	int originY;
	GameManager& gameManager = GameManager::getInstance();
	int brokenBrickNum;

	const int LEN_X = 41; // 가로
	const int LEN_Y = 30; // 세로

	Direction currentDirection;
	Direction originDirection;

	void DoubleReflectionCheck(Direction direction);
	Ball::Direction GetOppositeDirection(Direction direction);

public:
	Ball(int xPos, int yPos);

	void Init();

	int GetX();
	int GetY();
	void MoveRight();
	void MoveLeft();

	void Shoot(Direction direction);

	void Move();
	void OriginUpdate();
	bool GetIsBallMoving();
	void WallReflectionCheck();
	void BlockReflectionCheck();
	void ReflectionCheck();
	void OverlapCheck();

	int GetBrokenBrickNum() const;
	void InitBrokenBrickNum();
	void AddBrokenBrickNum();
};

