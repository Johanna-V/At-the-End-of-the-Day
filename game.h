#pragma once
#include "player.h"
#include "gamedata.h"

/*Stores the modes of the game*/
enum class GameMode {
	None,
	MainMenu,
	InGame,
};

//Declaration of the Game class that wraps/runs the game
class Game {
public:
	GameData gameData;
	Player player;

	void run();

private:
	//THIS ONE IS OBSOLETE AFTER ADDING GAME MODES: bool isRunning = true;
	void runMainMenu();
	void runGame();

	GameMode gameMode = GameMode::MainMenu;
};