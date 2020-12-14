#include <iostream>
#include "game.h"

//Definition of the Game class that runs the game
void Game::run() {
	// De-comment to print all locations
	std::cout << "Debugging Locations\n";
	gameData.debugLocations();
	
	std::cout << "Welcome to 'At the End of the Day'! Let's see what our day holds for us. \n";

	//Setting the player location to the start location. 
	//Player is lowercase here since this is the member of the Game class.
	//The Game class wraps around the Player (and GameData) struct.
	player.currentLocation = gameData.getStartLocation();

	//while loop for the game
	//isRunning is a member of the Game class and simply writing it here sets it to true
	//since that is what it is in the class
	while (isRunning) {

		//error handling
		if (player.currentLocation == nullptr) {
			std::cout << "Error. Player is not at a valid location! \n";
			break;
		}

		//print text for the player's current location
		std::cout << player.currentLocation->text << "\n\n";

		//if there are no choices for the current location, break the loop and print Game Over
		if (player.currentLocation->choices.size() == 0) {
			std::cout << "Game Over! \n";
			break;
		}

		std::cout << "Pick an option \n";

		//iterate through the size of the choices vector of the current location
		//and print the iteration number and the current choice's text
		for (unsigned int i = 0; i < player.currentLocation->choices.size(); ++i) {
			std::cout << "[" << i << "] " << player.currentLocation->choices[i].text << "\n";
		}

		//set a var for the user's input and set it to something outside of what the choice number will be
		//while the var 'choice' is less than 0 or larger than the total number of choices, 
		//ask for input to the var 'choice'
		int choice = -1;

		while (choice < 0 || choice >= player.currentLocation->choices.size()) {
			std::cin >> choice;
		}

		//set a var 'nextLocationId' to the locationId in the vector 'choices', that the player chose ('choice' var)
		//use the gameData function 'getLocationWithId' to search for and get the location with the chosen Id
		//increment the number of moves the player has made
		const std::string& nextLocationId = player.currentLocation->choices[choice].locationId;
		player.currentLocation = gameData.getLocationWithId(nextLocationId);
		player.moves++;
	}

	std::cout << "You made " << player.moves << " moves! \n";
}