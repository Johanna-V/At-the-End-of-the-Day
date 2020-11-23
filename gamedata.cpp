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