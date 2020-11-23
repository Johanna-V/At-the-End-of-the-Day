#pragma once
#include <string>
#include <vector>

//Represents the choices that a user can make after readin the text for a location (Id, Text)
struct LocationChoice {
	LocationChoice(const std::string& nextId, const std::string& aText); //Convenience constructor to create a location choice

	std::string locationId;	//The id for the location this choice leads to
	std::string text;		//The text to show for this location choice
};

//Represents a single location/paragraph in the game world. (Id, Text)
struct Location {
	Location(const std::string& anId, const std::string& aText); //Convenience constructor to create a location with an id and title
	std::string id; //A string representing the identifier for this location so we can find it later
	std::string text; //The text to display to the user when they enter this location
	std::vector<LocationChoice> choices; //An array/vector of choices the user can make at this location
};