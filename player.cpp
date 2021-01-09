#include "player.h"
#include "game.h"

//Inventory items will go here when it is time

/* If the bool 'hasVisitedLocation' is false for the id passed to this function,
add the id to the end of the visitedLocations vector*/
void Player::addVisitedLocation(const std::string& id) {
	if (hasVisitedLocation(id) == false) {
		visitedLocations.push_back(id);
	}
}

/*If the id passed to this function is the same as one of the locations in visitedLocations, 
the bool should get set to true*/
bool Player::hasVisitedLocation(const std::string& id) {
	for (size_t i = 0; i < visitedLocations.size(); ++i) {
		if (visitedLocations[i] == id) {
			return true;
		}
	}
	return false;
}