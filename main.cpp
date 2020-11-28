#include <iostream>
#include <string>
#include "game.h"

Game game;

int main()
{
	GameData gameData;

	Location* startLocation = gameData.getStartLocation();

	if (startLocation == nullptr) {
		std::cout << "No start location found - something went wrong? \n";
		return 1;
	}

	std::cout << "Start Location is " << startLocation->id << ": " << startLocation->text << "\n";


	//THIS THING IS BROKEN
	if (startLocation->choices.size() > 0) {
		const std::string& secondLocationId = startLocation->choices[0].nextLocationId;
		Location* secondLocation = gameData.getLocationWithId(secondLocation);

		if (secondLocation != nullptr) {
			std::cout << "Possible Second Location: " << secondLocation->text << "\n";
		}

	return (0);
}