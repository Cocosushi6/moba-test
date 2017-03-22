#include "world.h"

using namespace std;
using namespace World;

GameMap::GameMap(string pathToObj, string pathToGridFile) {
	this->model = new Model(pathToObj);
	this->grid = new MapGrid(pathToGridFile);
}

MapGrid::MapGrid(string data, bool remote) {
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

MapGrid::MapGrid(bool remote) {
	pugi::xml_parse_result result = tmxFile.load_file("map_data.tmx");
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


}
