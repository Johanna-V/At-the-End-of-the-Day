#include <iostream>
#include <string>

#include "gamedata.h"

int main()
{
	std::cout << "Hello World." << "\n";
	/*****END OF MAIN START TEST*****/

	bool gameOver = false;

	while (gameOver == false) {
		std::cout << "The game loop is running." << "\n";
		/*****END OF GAME START TEST*****/

		Location room1("start", "You are in the first room!");
		room1.choices.push_back(LocationChoice("room2", "Go North"));
		room1.choices.push_back(LocationChoice("exit", "Exit"));

		Location room2("room2", "You are in the second room of this story.");
		room2.choices.push_back(LocationChoice("exit", "Exit"));

		Location exit("exit", "This is the exit! :o");

		/*****BELOW ENDS GAME LOOP*****/
		gameOver = true;
		std::cout << "GAME OVER" << "\n";
	}

	return (0);
}