#pragma once
#include "player.h"
#include "gamedata.h"

//Declaration of the Game class that wraps/runs the game
class Game {
public:
	GameData gameData;
	Player player;

	void run();

private:
	bool isRunning = true;
};