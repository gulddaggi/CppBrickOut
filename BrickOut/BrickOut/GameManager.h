#pragma once
#include <vector>

class GameManager {
private:
	GameManager() {}
	GameManager(const GameManager& ref) {}
	GameManager& operator=(const GameManager& ref) {}
	~GameManager() {}

public:
	std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

	static GameManager& getInstance() {
		static GameManager s;
		return s;
	}
};

