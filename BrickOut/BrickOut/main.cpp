#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Ball.h"
#include "Bar.h"
#include <vector>

const int LEN_X = 41; // 가로
const int LEN_Y = 30; // 세로

#define LEFT 75
#define RIGHT 77
#define UP 72

void DrawGame(int x, int y, GameManager& gameManager)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (gameManager.frame[i][j] == 1) std::cout << "▦";
			else if (gameManager.frame[i][j] == 2) std::cout << "■";
			else if (gameManager.frame[i][j] == 3) std::cout << "◆";
			else std::cout << "  ";
		}
		std::cout << '\n';
	}
	std::cout << "Score : " << gameManager.GetTotalScore() << '\n';
}

int main()
{
	system("mode con:cols=100 lines=40 | title Title");
	GameManager& gameManager = GameManager::getInstance();
	std::vector<std::vector<int>>& gameFrame = gameManager.frame;

	// 마우스 커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	Bar bar(7, LEN_X/2 +1, LEN_Y-1);
	Ball ball(LEN_X/2, LEN_Y-2);

	gameManager.DrawStage(ball, bar);
	
	system("cls");
	DrawGame(LEN_X, LEN_Y, gameManager);
	

	while (true)
	{
		if (ball.GameOverCheck())
		{
			break;
		}

		if (ball.GetIsBallMoving())
		{
			ball.ReflectionCheck();
			gameFrame[ball.GetY()][ball.GetX()] = 0;
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
							gameFrame[ball.GetY()][ball.GetX()] = 0;
							ball.Shoot(Ball::Direction::UPRIGHT);
						}
						break;
					case LEFT:
						gameFrame[bar.GetY()][bar.GetRight()-1] = 0;
						bar.MoveLeft();
						if (bar.GetIsBallOnTheBar() && !bar.GetIsWallOnSide())
						{
							gameFrame[ball.GetY()][ball.GetX()] = 0;
							ball.MoveLeft();
						}
						break;
					case RIGHT:
						gameFrame[bar.GetY()][bar.GetLeft()] = 0;
						bar.MoveRight();
						if (bar.GetIsBallOnTheBar() && !bar.GetIsWallOnSide())
						{
							gameFrame[ball.GetY()][ball.GetX()] = 0;
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
			gameFrame[bar.GetY()][i] = 1;
		}

		gameFrame[ball.GetY()][ball.GetX()] = 3;
		COORD pos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		DrawGame(LEN_X, LEN_Y, gameManager);
		Sleep(100);
	}
	return 0;
}

