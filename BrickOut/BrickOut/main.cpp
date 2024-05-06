#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>

const int LEN_X = 41; // 가로
const int LEN_Y = 30; // 세로

#define LEFT 75
#define RIGHT 77
#define UP 72

std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

class Ball 
{
public:
	int x;
	int y;
	bool isBallMoving;
	int originX;
	int originY;

	enum class Direction
	{
		UPRIGHT,
		UPLEFT,
		DOWNRIGHT,
		DOWNLEFT
	};

	Direction currentDirection;
	Direction originDirection;

	Ball(int xPos, int yPos)
	{
		x = xPos;
		y = yPos;
		currentDirection = Direction::UPRIGHT;
		isBallMoving = false;
		OriginUpdate();
	}

	int GetX()
	{
		return x;
	}

	int GetY()
	{
		return y;
	}

	void MoveRight()
	{
		++x;
	}

	void MoveLeft()
	{
		--x;
	}

	bool GameOverCheck()
	{
		if (y == LEN_Y-1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void ReflectionCheck()
	{
		WallReflectionCheck();
		BlockReflectionCheck();
	}

	void Shoot(Direction direction)
	{
		isBallMoving = true;
		currentDirection = direction;
	}

	void Move()
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

	void OriginUpdate()
	{
		originX = x;
		originY = y;
		originDirection = currentDirection;
	}

	bool GetIsBallMoving()
	{
		return isBallMoving;
	}

	// 공이 벽, 발판에 충돌
	void WallReflectionCheck()
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
		else if (x == LEN_X-2)
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
		else if (y == LEN_Y-2 && frame[y+1][x] == 1)
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

	void BlockReflectionCheck()
	{
		//왼쪽
		if (frame[y][x - 1] == 2)
		{
			frame[y][x - 1] = 0;
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
		else if (frame[y][x + 1] == 2)
		{
			frame[y][x + 1] = 0;
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
		else if (frame[y - 1][x] == 2)
		{
			frame[y - 1][x] = 0;
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
		else if (frame[y + 1][x] == 2)
		{
			frame[y + 1][x] = 0;
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

	void OverlapCheck()
	{
		if (frame[y][x] != 0)
		{
			frame[y][x] = 0;
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
};

class Bar
{
public:
	int left;
	int right;
	int y;
	bool isBallOnTheBar = true;
	bool isWallOnSide = false;

	Bar(int size, int middle, int yPos)
	{
		left = middle - (size / 2)-1;
		right = middle + (size / 2);
		y = yPos;
	}

	int GetY()
	{
		return y;
	}

	int GetLeft()
	{
		return left;
	}

	int GetRight()
	{
		return right;
	}

	bool GetIsBallOnTheBar()
	{
		return isBallOnTheBar;
	}

	bool GetIsWallOnSide()
	{
		return isWallOnSide;
	}

	void SetIsBallOnTheBar(bool value)
	{
		isBallOnTheBar = value;
	}

	void MoveLeft()
	{
		if (left != 1)
		{
			isWallOnSide = false;
			--left;
			--right;
		}
		else isWallOnSide = true;
	}

	void MoveRight()
	{
		if (right != LEN_X - 1)
		{
			isWallOnSide = false;
			++left;
			++right;
		}
		else isWallOnSide = true;
	}
};

void DrawGame(int x, int y)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (frame[i][j] == 1) std::cout << "▦";
			else if (frame[i][j] == 2) std::cout << "■";
			else if (frame[i][j] == 3) std::cout << "◆";
			else std::cout << "  ";
		}
		std::cout << '\n';
	}
}

int main()
{
	system("mode con:cols=100 lines=40 | title Title");

	// 마우스 커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// 초기화
	for (int i = 0; i < LEN_Y; i++)
	{
		std::vector<int> row(LEN_X, 0);
		frame.push_back(row);
	}

	// 채울 좌표 지정
	// 테두리
	for (int i = 0; i < LEN_Y; i++)
	{
		for (int j = 0; j < LEN_X; j++)
		{
			if (i == 0 || j == 0 || j == LEN_X - 1) frame[i][j] = 1;
			else frame[i][j] = 0;
		}
	}

	// 블록
	for (int i = 4; i < 10; i++)
	{
		for (int j = 3; j < LEN_X - 3; j++)
		{
			frame[i][j] = 2;
		}
	}

	Bar bar(7, LEN_X/2 +1, LEN_Y-1);

	// 발판
	for (int i = bar.GetLeft(); i < bar.GetRight(); i++)
	{
		frame[bar.GetY()][i] = 1;
	}

	Ball ball(LEN_X/2, LEN_Y-2);

	// 공
	frame[ball.GetY()][ball.GetX()] = 3;
	
	system("cls");
	DrawGame(LEN_X, LEN_Y);
	

	while (true)
	{
		if (ball.GameOverCheck())
		{
			break;
		}

		if (ball.GetIsBallMoving())
		{
			ball.ReflectionCheck();
			frame[ball.GetY()][ball.GetX()] = 0;
			ball.Move();
		}

		int inputKey;
		if (_kbhit())
		{
			inputKey = _getch();
			if (inputKey == 224)
			{
				inputKey = _getch();
				switch (inputKey)
				{
					case UP:
						if (bar.GetIsBallOnTheBar() && !ball.GetIsBallMoving())
						{
							bar.SetIsBallOnTheBar(false);
							frame[ball.GetY()][ball.GetX()] = 0;
							ball.Shoot(Ball::Direction::UPRIGHT);
						}
						break;
					case LEFT:
						frame[bar.GetY()][bar.GetRight()-1] = 0;
						bar.MoveLeft();
						if (bar.GetIsBallOnTheBar() && !bar.GetIsWallOnSide())
						{
							frame[ball.GetY()][ball.GetX()] = 0;
							ball.MoveLeft();
						}
						break;
					case RIGHT:
						frame[bar.GetY()][bar.GetLeft()] = 0;
						bar.MoveRight();
						if (bar.GetIsBallOnTheBar() && !bar.GetIsWallOnSide())
						{
							frame[ball.GetY()][ball.GetX()] = 0;
							ball.MoveRight();
						}
						break;
					default:
						break;
				}
			}

		}
		// 발판 업데이트
		for (int i = bar.GetLeft(); i < bar.GetRight(); i++)
		{
			frame[bar.GetY()][i] = 1;
		}

		frame[ball.GetY()][ball.GetX()] = 3;
		COORD pos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		DrawGame(LEN_X, LEN_Y);
		Sleep(100);
	}
	return 0;
}

