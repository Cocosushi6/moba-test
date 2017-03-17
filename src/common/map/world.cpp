#include "world.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace World;

Map::Map(string pathToObj, string pathToGridFile) {
	this->model = new Model(pathToObj);
	this->grid = new MapGrid(pathToGridFile);
}

int MapGrid::load(string path) {

	return 0;
}
