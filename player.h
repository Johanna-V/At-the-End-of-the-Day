#pragma once
#include "gamedata.h"

//A Player struct
struct Player {
	//These functions are a part of saving and loading progress
	std::string name;
	void addVisitedLocation(const std::string& id);
	bool hasVisitedLocation(const std::string& id);
	std::vector<std::string> visitedLocations;

	//Keeps track of the player's currentLocation with a pointer to it 
	Location* currentLocation = nullptr;
	//...and their number of moves
	int moves = 0;
};