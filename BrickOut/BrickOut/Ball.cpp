#include "Ball.h"

Ball::Ball(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	currentDirection = Direction::UPRIGHT;
	isBallMoving = false;
	OriginUpdate();
}

int Ball::GetX()
{
	return x;
}

int Ball::GetY()
{
	return y;
}

void Ball::MoveRight()
{
	++x;
}

void Ball::MoveLeft()
{
	--x;
}

bool Ball::GameOverCheck()
{
	if (y == LEN_Y - 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Ball::ReflectionCheck()
{
	WallReflectionCheck();
	BlockReflectionCheck();
}

void Ball::Shoot(Direction direction)
{
	isBallMoving = true;
	currentDirection = direction;
}

void Ball::Move()
{
	isBallMoving = true;
	switch (currentDirection)
	{
	case Direction::UPRIGHT:
		++x;
		--y;
		break;
	case Direction::UPLEFT:
		--x;
		--y;
		break;
	case Direction::DOWNRIGHT:
		++x;
		++y;
		break;
	case Direction::DOWNLEFT:
		--x;
		++y;
		break;
	default:
		break;
	}
	OverlapCheck();
	OriginUpdate();
}

void Ball::OriginUpdate()
{
	originX = x;
	originY = y;
	originDirection = currentDirection;
}

bool Ball::GetIsBallMoving()
{
	return isBallMoving;
}

// 공이 벽, 발판에 충돌
void Ball::WallReflectionCheck()
{
	// 왼쪽 벽
	if (x == 1)
	{
		if (currentDirection == Direction::UPLEFT)
		{
			currentDirection = Direction::UPRIGHT;
		}
		else if (currentDirection == Direction::DOWNLEFT)
		{
			currentDirection = Direction::DOWNRIGHT;
		}
		// 위쪽 벽 복수충돌
		if (y == 1)
		{
			currentDirection = Direction::DOWNRIGHT;
		}
	}
	// 오른쪽 벽
	else if (x == LEN_X - 2)
	{
		if (currentDirection == Direction::UPRIGHT)
		{
			currentDirection = Direction::UPLEFT;
		}
		else if (currentDirection == Direction::DOWNRIGHT)
		{
			currentDirection = Direction::DOWNLEFT;
		}

		// 위쪽 벽 복수충돌
		if (y == 1)
		{
			currentDirection = Direction::DOWNLEFT;
		}
	}
	// 위쪽 벽
	else if (y == 1)
	{
		if (currentDirection == Direction::UPLEFT)
		{
			currentDirection = Direction::DOWNLEFT;
		}
		else if (currentDirection == Direction::UPRIGHT)
		{
			currentDirection = Direction::DOWNRIGHT;
		}
	}
	// 발판
	else if (y == LEN_Y - 2 && GameManager::getInstance().frame[y + 1][x] == 1)
	{
		if (currentDirection == Direction::DOWNRIGHT)
		{
			currentDirection = Direction::UPRIGHT;
		}
		else if (currentDirection == Direction::DOWNLEFT)
		{
			currentDirection = Direction::UPLEFT;
		}
	}
}

void Ball::BlockReflectionCheck()
{
	//왼쪽
	if (gameManager.frame[y][x - 1] == 2)
	{
		gameManager.frame[y][x - 1] = 0;
		if (currentDirection == Direction::UPLEFT)
		{
			currentDirection = Direction::UPRIGHT;
		}
		else if (currentDirection == Direction::DOWNLEFT)
		{
			currentDirection = Direction::DOWNRIGHT;
		}
	}
	// 오른쪽
	else if (gameManager.frame[y][x + 1] == 2)
	{
		gameManager.frame[y][x + 1] = 0;
		if (currentDirection == Direction::UPRIGHT)
		{
			currentDirection = Direction::UPLEFT;
		}
		else if (currentDirection == Direction::DOWNRIGHT)
		{
			currentDirection = Direction::DOWNLEFT;
		}
	}
	// 위쪽
	else if (gameManager.frame[y - 1][x] == 2)
	{
		gameManager.frame[y - 1][x] = 0;
		if (currentDirection == Direction::UPLEFT)
		{
			currentDirection = Direction::DOWNLEFT;
		}
		else if (currentDirection == Direction::UPRIGHT)
		{
			currentDirection = Direction::DOWNRIGHT;
		}
	}
	// 아래쪽
	else if (gameManager.frame[y + 1][x] == 2)
	{
		gameManager.frame[y + 1][x] = 0;
		if (currentDirection == Direction::DOWNRIGHT)
		{
			currentDirection = Direction::UPRIGHT;
		}
		else if (currentDirection == Direction::DOWNLEFT)
		{
			currentDirection = Direction::UPLEFT;
		}
	}
}

void Ball::OverlapCheck()
{
	if (gameManager.frame[y][x] != 0)
	{
		gameManager.frame[y][x] = 0;
		x = originX;
		y = originY;
		switch (currentDirection)
		{
		case Direction::UPRIGHT:
			currentDirection = Direction::DOWNLEFT;
			break;
		case Direction::UPLEFT:
			currentDirection = Direction::DOWNRIGHT;
			break;
		case Direction::DOWNRIGHT:
			currentDirection = Direction::UPLEFT;
			break;
		case Direction::DOWNLEFT:
			currentDirection = Direction::UPRIGHT;
			break;
		default:
			break;
		}
		Move();
	}
}