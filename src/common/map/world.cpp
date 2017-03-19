#include "world.h"

using namespace std;
using namespace World;

GameMap::GameMap(string pathToObj, string pathToGridFile) {
	this->model = new Model(pathToObj);
	this->grid = new MapGrid(pathToGridFile);
}

MapGrid::MapGrid(string path) {
	pugi::xml_parse_result result = tmxFile.load_file("");
}
