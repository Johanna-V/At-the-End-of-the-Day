#include "gamedata.h"

// Convenience constructor to create a location CHOICE with important properties set
LocationChoice::LocationChoice(const std::string& nextId, const std::string& aText)
{
	locationId = nextId;
	text = aText;
}

// Convenience constructor to create a LOCATION with important properties set
Location::Location(const std::string& anId, const std::string& aText)
{
	id = anId;
	text = aText;
}

GameData::GameData() {
	createLocations();
}

void GameData::debugLocations() {
	for (int i = 0; i < locations.size(); ++i) {
		Location location = locations[i];
		std::cout << location.id << ": " << location.text << "\n";
	}
}

void GameData::createLocations() {
	Location room1("start", "You are in the first room!");
	room1.choices.push_back(LocationChoice("room2", "Go North"));
	room1.choices.push_back(LocationChoice("exit", "Exit"));
	locations.push_back(room1);

	Location room2("room2", "You are in the second room of this story.");
	room2.choices.push_back(LocationChoice("exit", "Exit"));
	locations.push_back(room2);

	Location exit("exit", "This is the exit! :o");
	locations.push_back(exit);
}

Location* GameData::getStartLocation() {
	if (locations.size() == 0) {
		return nullptr;
	}
	return &locations[0];
}

Location* GameData::getLocationWithId(const std::string& id) {
	for (int i = 0; i < locations.size(); ++i) {
		if (locations[i].id == id) {
			return &locations[i];
		}
	}
	return nullptr;
}