#include "world.h"
#include "pugixml.hpp"

using namespace std;
using namespace World;

GameMap::GameMap() {
}

GameMap::GameMap(string pathToGridFile) {
	this->grid = new MapGrid(this);
}

GameMap::GameMap(MapGrid data) {
	this->grid = grid;
}

std::string GameMap::getMapPath() {
	return this->path;
}


MapGrid::MapGrid(string data, GameMap *map) {
	this->map = map;
	cout << "Loading MapGrid tmx file from data..." << endl;
	pugi::xml_parse_result result = tmxFile.load_string(data.c_str());
	if(result) {
		cout << "Data was parsed successfully. Generating tiles..." << endl;
		if(generateTiles() != 0) {
			cout << "Error while generating tiles" << endl;
		}

	} else {
		cout << "Error while parsing xml map data." << endl;
	}
}

MapGrid::MapGrid(GameMap *map) {
	this->map = map;
	pugi::xml_parse_result result = tmxFile.load_file(map->getMapPath().c_str());
	if(result) {
		cout << "File parsed successfully. Generating tiles..." << endl;
		if(generateTiles() != 0) {
			cout << "Error while generating tiles" << endl;
		}
	} else {
		cout << "Error while parsing xml map file." << endl;
	}
}


int MapGrid::generateTiles() {

	return 0;
}

sf::Packet& operator<<(sf::Packet& packet, const World::GameMap& game) {
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, World::GameMap& state) {
	return packet;
}
