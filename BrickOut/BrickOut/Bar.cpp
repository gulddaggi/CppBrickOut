#include "Bar.h"

Bar::Bar(int size, int middle, int yPos)
{
	left = middle - (size / 2) - 1;
	right = middle + (size / 2);
	y = yPos;
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