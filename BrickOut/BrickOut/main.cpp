#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>

const int LEN_X = 41; // 가로
const int LEN_Y = 30; // 세로

std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

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
	std::cout << "아무 키 + enter 입력하여 시작.\n";

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

	// 발판
	for (int i = 17; i < 24; i++)
	{
		frame[LEN_Y - 1][i] = 1;
	}

	// 공
	frame[LEN_Y - 2][20] = 3;

	getchar();
	system("cls");
	DrawGame(LEN_X, LEN_Y);

	while (true)
	{
		int inputKey;
		if (_kbhit())
		{
			COORD pos = { 0, 0 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
			DrawGame(LEN_X, LEN_Y);
		}
	}
	return 0;
}

