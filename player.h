#pragma once
#include "gamedata.h"

//A Player struct keeping track of the player's currentLocation with a pointer to it, 
//and their number of moves
struct Player {
	Location* currentLocation = nullptr;
	int moves = 0;
};