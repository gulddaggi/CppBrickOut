#include "Bar.h"

Bar::Bar(int size, int middle, int yPos)
{
	length = size;
	left = middle - (size / 2) - 1;
	right = middle + (size / 2);
	y = yPos;
}

void Bar::Init()
{
	int middle = gameManager.GetLENX() / 2 + 1;
	left = middle - (length / 2) - 1;
	right = middle + (length / 2);
	y = gameManager.GetLENY() - 1;
	isBallOnTheBar = true;
	isWallOnSide = false;
}

int Bar::GetLength()
{
	return length;
}

int Bar::GetY()
{
	return y;
}

int Bar::GetLeft()
{
	return left;
}

int Bar::GetRight()
{
	return right;
}

bool Bar::GetIsBallOnTheBar()
{
	return isBallOnTheBar;
}

void Bar::SetIsBallOnTheBar(bool value)
{
	isBallOnTheBar = value;
}

bool Bar::GetIsWallOnSide()
{
	return isWallOnSide;
}

void Bar::MoveLeft()
{
	if (left != 1)
	{
		isWallOnSide = false;
		--left;
		--right;
	}
	else isWallOnSide = true;
}

void Bar::MoveRight()
{
	if (right != LEN_X - 1)
	{
		isWallOnSide = false;
		++left;
		++right;
	}
	else isWallOnSide = true;
}