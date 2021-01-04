#include <iostream>
#include "game.h"

//Definition of the Game class that runs the game
void Game::run() {
	/* De-comment to print all locations
	std::cout << "Debugging Locations\n";
	gameData.debugLocations();*/

	std::cout << "Welcome to 'At the End of the Day'! Let's see what our day holds for us. \n";

	/*Guiding the game to the correct function depending on the GameMode*/
	while (gameMode != GameMode::None) {
		switch (gameMode) {
		case GameMode::MainMenu:
			runMainMenu();
			break;

		case GameMode::InGame:

				runGame();
				break;

		}
	}

	std::cout << "Thanks for playing! \n";

	std::cout << "You made " << player.moves << " moves! \n";
}

void Game::runMainMenu() {
	std::cout << "\n MAIN MENU \n";
	std::cout << "[1] Resume Game \n";
	std::cout << "[2] Exit Game \n";

	//NOT DONE
	while (true) {
		std::string menuInput;
		std::cout << "> ";
		std::getline(std::cin, menuInput);
		int menuChoice = 0;

		try {
			menuChoice = std::stoi(menuInput);
		}
		
		catch (std::exception ex) {
			std::cout << "Invalid menu input\n";
			continue;
		}

		if (menuChoice == 1) {
			gameMode = GameMode::InGame;
			return;
		}

		else if (menuChoice == 2) {
			gameMode = GameMode::None;
			return;
		}
	}

	
	
}

void Game::runGame() {

	/******* THIS WAS MOVED IN HERE BECAUSE OF THE GAME MODES.

	Setting the player location to the start location.
	Player is lowercase here since this is the member of the Game class.
	The Game class wraps around the Player (and GameData) struct.*/

	player.currentLocation = gameData.getStartLocation();

	while (gameMode==GameMode::InGame) {

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
			gameMode = GameMode::None;
			break;
		}

		std::cout << "Pick an option \n";

		//iterate through the size of the choices vector of the current location
		//and print the iteration number and the current choice's text
		for (unsigned int i = 0; i < player.currentLocation->choices.size(); ++i) {
			std::cout << "[" << i << "] " << player.currentLocation->choices[i].text << "\n";
		}

		//every time we print any choices from the current location, we then also print these choices:
		std::cout << "[m] Menu\n";
		std::cout << "[i] Inventory\n";

		//set a var for the user's input and set it to something outside of what the choice number will be
		//while the var 'choice' is less than 0 or larger than the total number of choices, 
		//ask for input to the var 'choice'
		bool validChoice = false;
		std::string input;
		int choice = -1;

		/*saving this just in case I mess up the new while loop that will cover menu choices
		while (choice < 0 || choice >= player.currentLocation->choices.size()) {
			std::cin >> choice;
		}*/

		/*Checking whether we can recognize the input or not*/
		while (validChoice == false) {
			std::cout << "> ";
			std::getline(std::cin, input);

			if (input.length() == 0) {
				continue;
			}

			if (input[0] == 'm' || input[0] == 'i' || input[0] == 'M' || input[0] == 'I') {
				validChoice = true;
			}

			else {
				try {
					choice = std::stoi(input); //John's game had "- 1" at the end of this but I included 0 in my player choices so I had to get rid of it
				}
				catch (std::exception ex) {}

				if (choice >= 0 && choice < (int)player.currentLocation->choices.size()) {
					validChoice = true;
				}
			}
		}

		//After the error handling loop, we can now deal with the input for real because we know it is valid

		if (input[0] == 'm' || input[0] == 'M') {
			//*********NOT DONE This function does not exist yet: handleInGameMenu();
			//In the meantime this is what we do instead:
			gameMode = GameMode::MainMenu;
		}
		else if (input[0] == 'i' || input[0] == 'I') {
			//*********NOT DONE This function does not exist yet: handleInventory()
			//In the meantime this is what we do instead:
			std::cout << "Sorry, no inventory yet.\n";
			gameMode = GameMode::MainMenu;
		}
		else {
			//set a var 'nextLocationId' to the locationId in the vector 'choices', that the player chose ('choice' var)
		//use the gameData function 'getLocationWithId' to search for and get the location with the chosen Id
		//increment the number of moves the player has made
			const std::string& nextLocationId = player.currentLocation->choices[choice].locationId;
			player.currentLocation = gameData.getLocationWithId(nextLocationId);
			player.moves++;
		}

		//set a var 'nextLocationId' to the locationId in the vector 'choices', that the player chose ('choice' var)
		//use the gameData function 'getLocationWithId' to search for and get the location with the chosen Id
		//increment the number of moves the player has made
		/*const std::string& nextLocationId = player.currentLocation->choices[choice].locationId;
		player.currentLocation = gameData.getLocationWithId(nextLocationId);
		player.moves++;*/
	}

}