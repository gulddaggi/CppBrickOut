#include "Ball.h"

Ball::Ball(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
	currentDirection = Direction::UPRIGHT;
	isBallMoving = false;
	brokenBrickNum = 0;
	OriginUpdate();
}

void Ball::Init()
{
	x = gameManager.GetLENX() / 2;
	y = gameManager.GetLENY() - 2;
	currentDirection = Direction::UPRIGHT;
	isBallMoving = false;
	brokenBrickNum = 0;
	OriginUpdate();
	InitBrokenBrickNum();
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

	if (y == LEN_Y - 1)
	{
		gameManager.GameOver();
	}
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
	if (y == LEN_Y - 2 &&
	(GameManager::getInstance().frame[y + 1][x] == 1 || GameManager::getInstance().frame[y + 1][x - 1] == 1 || GameManager::getInstance().frame[y + 1][x + 1] == 1))
	{
		if (currentDirection == Direction::DOWNRIGHT)
		{
			currentDirection = Direction::UPRIGHT;
		}
		else if (currentDirection == Direction::DOWNLEFT)
		{
			currentDirection = Direction::UPLEFT;
		}
		InitBrokenBrickNum();
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
		AddBrokenBrickNum();
		DoubleReflectionCheck(originDirection);
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
		AddBrokenBrickNum();
		DoubleReflectionCheck(originDirection);
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
		AddBrokenBrickNum();
		DoubleReflectionCheck(originDirection);
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
		AddBrokenBrickNum();
		DoubleReflectionCheck(originDirection);
	}
	// 왼쪽 위 대각선
	else if (gameManager.frame[y - 1][x - 1] == 2 && currentDirection == Direction::UPLEFT)
	{
		gameManager.frame[y - 1][x - 1] = 0;
		currentDirection = Direction::UPRIGHT;
		AddBrokenBrickNum();
	}
	// 오른쪽 위 대각선
	else if (gameManager.frame[y - 1][x + 1] == 2 && currentDirection == Direction::UPRIGHT)
	{
		gameManager.frame[y - 1][x + 1] = 0;
		currentDirection = Direction::DOWNRIGHT;
		AddBrokenBrickNum();
	}
	// 왼쪽 아래 대각선
	else if (gameManager.frame[y + 1][x - 1] == 2 && currentDirection == Direction::DOWNLEFT)
	{
		gameManager.frame[y + 1][x - 1] = 0;
		currentDirection = Direction::DOWNRIGHT;
		AddBrokenBrickNum();
	}
	//오른쪽 아래 대각선
	else if (gameManager.frame[y + 1][x + 1] == 2 && currentDirection == Direction::DOWNRIGHT)
	{
		gameManager.frame[y + 1][x + 1] = 0;
		currentDirection = Direction::UPRIGHT;
		AddBrokenBrickNum();
	}
}

void Ball::OverlapCheck()
{
	if (gameManager.frame[y][x] != 0)
	{
		if (gameManager.frame[y][x] == 2)
		{
			gameManager.frame[y][x] = 0;
			AddBrokenBrickNum();
		}

		x = originX;
		y = originY;

		currentDirection = GetOppositeDirection(currentDirection);
		Move();
	}
}

void Ball::DoubleReflectionCheck(Direction direction)
{
	// 이중 반사 확인
	switch (direction)
	{
		// 위, 우측 블록 확인
		case Ball::Direction::UPRIGHT:
			if (gameManager.frame[y - 1][x] == 2)
			{
				gameManager.frame[y - 1][x] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			else if (gameManager.frame[y][x + 1] == 2)
			{
				gameManager.frame[y][x + 1] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			break;
		// 위, 좌측 블록 확인
		case Ball::Direction::UPLEFT:
			if (gameManager.frame[y - 1][x] == 2)
			{
				gameManager.frame[y - 1][x] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			else if (gameManager.frame[y][x - 1] == 2)
			{
				gameManager.frame[y][x - 1] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			break;
		// 아래, 우측 블록 확인
		case Ball::Direction::DOWNRIGHT:
			if (gameManager.frame[y + 1][x] == 2)
			{
				gameManager.frame[y + 1][x] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			else if (gameManager.frame[y][x + 1] == 2)
			{
				gameManager.frame[y][x + 1] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			break;
		// 아래, 좌측 블록 확인
		case Ball::Direction::DOWNLEFT:
			if (gameManager.frame[y + 1][x] == 2)
			{
				gameManager.frame[y + 1][x] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			else if (gameManager.frame[y][x - 1] == 2)
			{
				gameManager.frame[y][x - 1] = 0;
				currentDirection = GetOppositeDirection(originDirection);
				AddBrokenBrickNum();
			}
			break;
		default:
			break;
	}
}

Ball::Direction Ball::GetOppositeDirection(Direction direction)
{
	Direction returnDirection;
	switch (direction)
	{
		case Ball::Direction::UPRIGHT:
			returnDirection = Ball::Direction::DOWNLEFT;
			break;
		case Ball::Direction::UPLEFT:
			returnDirection = Ball::Direction::DOWNRIGHT;
			break;
		case Ball::Direction::DOWNRIGHT:
			returnDirection = Ball::Direction::UPLEFT;
			break;
		case Ball::Direction::DOWNLEFT:
			returnDirection = Ball::Direction::UPRIGHT;
			break;
		default:
			break;
	}
	return returnDirection;
}

int Ball::GetBrokenBrickNum() const
{
	return brokenBrickNum;
}

void Ball::InitBrokenBrickNum()
{
	brokenBrickNum = 0;
}

void Ball::AddBrokenBrickNum()
{
	++brokenBrickNum;
	gameManager.DecreaseBrickCount();
	gameManager.CalcScore(brokenBrickNum);
}

