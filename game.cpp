#include <iostream>
#include "game.h"

//String with the filename to use when saving and loading from the menu
const std::string SAVE_PATH = "save_game.txt";

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
	std::cout << "[1] Start Game \n";
	std::cout << "[2] Load Game \n";
	std::cout << "[3] Exit Game \n";

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

		//There is something wrong here
		if (menuChoice == 2) {
			loadGame(SAVE_PATH);
			gameMode = GameMode::InGame;
			return;
		}
		else if (menuChoice == 3) {
			gameMode = GameMode::None;
			return;
		}
	}

	
	
}

void Game::runGame() {

	/*Setting the player location to the start location.
	Player is lowercase here since this is the member of the Game class.
	The Game class wraps around the Player (and GameData) struct.*/

	/*the below line is blocking "Load Game" from working when in runMainMenu() 
	(if the game is already running, there is no problem)
	However, if I remove it from here, "Start Game" will not work. How do i solve this?*/
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
			handleInGameMenu();
			//gameMode = GameMode::MainMenu;
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

	}

}

void Game::handleInGameMenu() {
	std::cout << "\n" << "Please select an option.\n";
	std::cout << " [1] Continue Game\n";
	std::cout << " [2] Save Game\n";
	std::cout << " [3] Load Last Save\n";
	std::cout << " [4] Exit Game\n";

	while (true) {
		std::string gamemenuInput;
		std::cout << "> ";
		std::getline(std::cin, gamemenuInput);
		int gamemenuChoice = 0;

		//Handling exceptions
		try {
			gamemenuChoice = std::stoi(gamemenuInput);
		}
		catch (std::exception ex) {
			std::cout << "Invalid game menu input.\n";
			continue;
		}

		/*Go back to the game. The game will not restart from the beginning
		since we are using this handleInGameMenu() function and "return" here.
		return just goes back to where we were before running this function.
		I am still confused as to why we have a separate runMainMenu() function though 
		- I think it is because the player should only be able to save if they are currently playing.*/
		if (gamemenuChoice == 1) {
			gameMode = GameMode::InGame;
			return;
		}

		//Save the current game (staying in the menu)
		if (gamemenuChoice == 2) {
			saveGame(SAVE_PATH);
			return;
		}

		else if (gamemenuChoice == 3) {
			loadGame(SAVE_PATH);
			gameMode = GameMode::InGame;
			return;
		}

		//Exit the game (without saving)
		else if (gamemenuChoice == 4) {
			gameMode = GameMode::None;
			return;
		}

	}

}

void Game::saveGame(const std::string& path) {
	//Open a file to output stuff to
	std::ofstream file(path);

	//Display error if the file can't be created/opened
	if (file.is_open() == false) {
		std::cout << "Failed to write save game: " << path << "\n";
		return;
	}

	//Now output things to the file

	/* No player name yet :(
	file << player.name << "\n";*/

	file << player.currentLocation->id << "\n";

	file << player.moves << "\n";

	//Inventory stuff can go here when there is one

	//Comma separated list of visited locations (for later)
	for (size_t i = 0; i < player.visitedLocations.size(); ++i) {
		if (i > 0) {
			file << ",";
		}
		file << player.visitedLocations[i];
	}
	file << "\n";
}

void Game::loadGame(const std::string& path) {
	//Open a file to read
	std::ifstream file(path);

	//Display error if the file can't be opened
	if (file.is_open() == false) {
		std::cout << "Failed to read save game: " << path << "\n";
		return;
	}

	//Now we read the file content line by line
	std::string line;

	/*I don't have any player name yet...:(
	1: Player Name
	std::getline(file, line);
	player.name = line;*/

	//2: Send the player to the saved current location
	std::getline(file, line);
	player.currentLocation = gameData.getLocationWithId(line);

	//3: Use the number of moves from the save
	std::getline(file, line);
	player.moves = std::stoi(line);

	/* This seems to use something from the inventory stuff that I have been skipping, so let's wait with this
	std::getline(file, line);
	player.visitedLocations = split(line, ',');
	*/
}