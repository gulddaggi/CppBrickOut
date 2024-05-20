#include "GameManager.h"
#include "Ball.h"
#include "Bar.h"

GameManager& GameManager::getInstance() {
	static GameManager s;
	return s;
}

void GameManager::DrawStage(Ball& ball, Bar& bar)
{
	isStageClear = false;

	switch (curStage)
	{
		case 1:
			DrawStage1(ball, bar);
			break;

		case 2:
			DrawStage2(ball, bar);
			break;

		default:
			break;
	}
}

void GameManager::DrawStage1(Ball& ball, Bar& bar)
{
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
	for (int i = 3; i < 11; i++)
	{
		for (int j = 1; j < LEN_X - 1; j++)
		{
			if (i % 2 == 1) break;
			
			frame[i][j] = 2;
			++brickCount;
		}
	}

	// 발판
	for (int i = bar.GetLeft(); i < bar.GetRight(); i++)
	{
		frame[bar.GetY()][i] = 1;
	}

	// 공
	frame[ball.GetY()][ball.GetX()] = 3;
}

void GameManager::DrawStage2(Ball& ball, Bar& bar)
{
	isStageClear = false;

	// 초기화
	for (int i = 0; i < LEN_Y; i++)
	{
		for (int j = 0; j < LEN_X; j++)
		{
			frame[i][j] = 0;
		}
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

	int min = 3;
	int max = 17;
	int count = 1;
	int mid = LEN_X / 2;

	// 블록
	for (int i = min; i <= max; i++)
	{
		if (count == 1)
		{
			frame[i][mid] = 2;
			++brickCount;
		}
		else
		{
			for (int j = mid - count/2; j <= mid + count/2; j++)
			{
				frame[i][j] = 2;
				++brickCount;
			}
		}

		if (i < (min + max) / 2)
		{
			count += 2;
		}
		else
		{
			count -= 2;
		}
	}

	// 발판
	for (int i = bar.GetLeft(); i < bar.GetRight(); i++)
	{
		frame[bar.GetY()][i] = 1;
	}

	// 공
	frame[ball.GetY()][ball.GetX()] = 3;
}

void GameManager::StageClear()
{
	if (curStage <= 2)
	{
		++curStage;
	}
}

int GameManager::GetLENX() const
{
	return LEN_X;
}

int GameManager::GetLENY() const
{
	return LEN_Y;
}

int GameManager::GetTotalScore() const
{
	return totalScore;
}

void GameManager::CalcScore(int brokenBrickNum)
{
	if (brokenBrickNum >= 1)
	{
		if (brokenBrickNum > 1) totalScore += 100 + (brokenBrickNum-1) * 10;
		else totalScore += 100;
	}
}

void GameManager::UpdateBrickCount(int value)
{
	brickCount = 0;
	brickCount = value;

	if (brickCount == 0)
	{
		isStageClear = true;
		++curStage;
		if (curStage > 2) isGameClear = true;
	}
}

int GameManager::GetBrickCount() const
{
	return brickCount;
}

bool GameManager::GetIsStageClear() const
{
	return isStageClear;
}

bool GameManager::GetIsGameClear() const
{
	return isGameClear;
}

bool GameManager::GetIsGameOver() const
{
	return isGameOver;
}

void GameManager::GameClear()
{
	isGameClear = true;
}

void GameManager::GameOver()
{
	isGameOver = true;
}

void GameManager::Restart(Ball& ball, Bar& bar)
{
	ball.Init();
	bar.Init();
	curStage = 1;
	score = 0;
	totalScore = 0;
	brickCount = 0;
	isStageClear = false;
	isGameClear = false;
	isGameOver = false;

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
	for (int i = 3; i < 11; i++)
	{
		for (int j = 1; j < LEN_X - 1; j++)
		{
			if (i % 2 == 1) break;

			frame[i][j] = 2;
			++brickCount;
		}
	}

	// 발판
	for (int i = bar.GetLeft(); i < bar.GetRight(); i++)
	{
		frame[bar.GetY()][i] = 1;
	}

	// 공
	frame[ball.GetY()][ball.GetX()] = 3;

}