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
	createLocations(); //The first location is in here, below and loads with this function call
	InitializeLocations(); //The rest of the locations are in a text file that this loads them from
}

void GameData::debugLocations() {
	for (int i = 0; i < locations.size(); ++i) {
		Location location = locations[i];
		std::cout << location.id << ": " << location.text << "\n";
	}
}

void GameData::createLocations() {
	Location room1("start", "You are in the first room!");
	room1.choices.push_back(LocationChoice("bed01", "Wake up"));
	room1.choices.push_back(LocationChoice("exit", "Exit"));
	locations.push_back(room1);

	//Trying to get the game to use the text file locations instead but there are problems
	/*Location room2("room2", "You are in the second room of this story.");
	room2.choices.push_back(LocationChoice("exit", "Exit"));
	locations.push_back(room2);

	Location exit("exit", "This is the exit! :o");
	locations.push_back(exit);*/
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

//Opens and parses the text file that contains most of the locations
int GameData::loadLocationData(const std::string& path) {

	//Open locations file
	std::ifstream locationsFile(path);
	int locationsAdded = 0;

	if (locationsFile.is_open() == false) {
		std::cout << "Could not load locations.\n";
		return 0;
	}

	//"create a location object called "workingLocation" with empty ID and Text"
	Location workingLocation("", "");
	
	std::string line;
	std::string locationID;

	if (locationsFile.is_open()) {

		while (std::getline(locationsFile, line)) {
			//Error handling from my saviour, Ingeborg! Skips forward if first character is /
			if (line.length() == 0 || line[0] == '/') {
				continue;
			}

			if (line[0] == '#') {
				//process the line to remove the '#' and figure out the 'id' of the room
				//we make a substring from pos 1 (which is after the # on pos 0) to the end position and set that as the id
				locationID = line.substr(1, line.npos);
				//set workingLocation.id to the id
				workingLocation.id = locationID;
				continue;
			}

			//Find the ':' character in the string using line.find. Use substr to extract the "nextLocationId" 
			//and "choice text" from the line. Create a new choice object and add it to workingLocation
			if (line[0] == '&') {
				unsigned __int64 colonIndex = line.find(':');
				std::string nextId = line.substr(1, colonIndex - 1);
				std::string locdesc = line.substr(colonIndex + 1, line.npos);
				workingLocation.choices.push_back(LocationChoice(nextId, locdesc));
				continue;
			}

			// This line means we should "commit" the current "workingLocation", and clear the ID, Text and Choices 
			//in workingLocation(or create a new workingLocation), add one to locationsAdded
			if (line[0] == '=')
			{
				//add the current "workingLocation" object to your location list
				//"location" may be the problem here if something breaks
				locations.push_back(workingLocation);
				workingLocation.choices.clear();
				workingLocation.id.clear();
				++locationsAdded;
				continue;
			}
			else {
				workingLocation.text += line.substr(0, line.npos) + "\n";
			}
		}

		locationsFile.close();
		return true;
	}
	else {
	std::cout << "Unable to open " << path << "Please check that the path is correct";
	}
	return false;
}	

//This is what actually loads the locations from the text file
void GameData::InitializeLocations()
{
	//I only have one file so far but I might add more at some point
	for (int i = 1; i <= 1; i++)
	{
		std::string fileToLoad = "locations" + std::to_string(i) + ".txt";
		bool load = loadLocationData(fileToLoad);
		if (!load)
		{
			std::cout << "Warning couldn't load" << fileToLoad << " double check the adress exists\n";
			return;//break loop if a file could not load a file
		}
	}
}