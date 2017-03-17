#ifndef SRC_CLIENT_WORLD_H_
#define SRC_CLIENT_WORLD_H_

#include <string>
#include <iostream>
#include <vector>

#include "rendering/model.h"


namespace World {

	enum MapGridTileType {
		NORMAL, SOLID, WATER
	};

	class MapGridTile {
		public:
			MapGridTile(int width, int height);
		private:
			MapGridTileType type;
			int width, height;
	};

	class MapGrid {
		public:
			MapGrid(std::string path);
			~MapGrid();
			int load(std::string path); //TODO add XML loader for grid file
		private:
			std::vector<MapGridTile, MapGridTile> tiles; //TODO search for two dimensional vectors in cpp
	};

	class Map {
		public:
			Map(std::string pathToObj, std::string pathToGridFile);
			~Map();
		private:
			std::string path;
			MapGrid *grid;
			Model *model;
	};

}


#endif /* SRC_CLIENT_WORLD_H_ */
