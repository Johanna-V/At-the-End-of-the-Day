#include <iostream>
#include <string>
#include "game.h"

Game game;

int main() {
	//game.run();

	GameData gameData;
	Location* startLocation = gameData.getStartLocation();

	if (startLocation == nullptr) {
		std::cout << "No start location found - something went wrong? \n";
		return 1;
	}

	std::cout << "Start Location is " << startLocation->id << ": " << startLocation->text << "\n";

	//If there are more than one item in the choices vector of the startLocation, set a local var to the location id of the first choice in the startLocation
	//Then set a local var to a specific room id that we provide locally here
	//If the location we asked for exists, print its text
	if (startLocation->choices.size() > 0) {
		const std::string& secondLocationId = startLocation->choices[0].locationId;
		Location* secondLocation = gameData.getLocationWithId("room2");

		if (secondLocation != nullptr) {
			std::cout << "Possible Second Location: " << secondLocation->text << "\n";
		}

		return (0);
	}
}