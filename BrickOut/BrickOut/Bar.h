#pragma once

class Bar
{
private:
	int left;
	int right;
	int y;
	bool isBallOnTheBar = true;
	bool isWallOnSide = false;
	const int LEN_X = 41; // 가로
	const int LEN_Y = 30; // 세로

public:
	Bar(int size, int middle, int yPos);

	int GetY();
	int GetLeft();
	int GetRight();

	bool GetIsBallOnTheBar();
	void SetIsBallOnTheBar(bool value);
	bool GetIsWallOnSide();

	void MoveLeft();
	void MoveRight();
};

