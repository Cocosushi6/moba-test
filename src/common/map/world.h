#ifndef SRC_CLIENT_WORLD_H_
#define SRC_CLIENT_WORLD_H_

#include <string>
#include <iostream>
#include <vector>

#include "tmxlite/Map.hpp"
#include "pugixml.hpp"


namespace World {

	class Tile {
		public:
			Tile(int x, int y, int z, int size, bool solid);
		private:
			int x, y, z; //are ints because tiles are next to each other. Z is the equivalent of heightZ or layerZ variables for entities
			int size = 32;
			bool solid = false;
	};

	class MapGrid {
		public:
			MapGrid(bool remote); //load this one by getting Map's pathToTmx file with getter
			MapGrid(std::string data, bool remote);
			int parseMap();
			~MapGrid();
		private:
			int generateTiles();
			pugi::xml_document tmxFile;
			std::vector<std::vector<Tile>> tiles;
	};

	class GameMap {
		public:
			GameMap(std::string pathToObj, std::string pathToTmxFile);
			GameMap(std::string pathToObj, MapGrid data);
			~GameMap();
		private:
			std::string path;
			MapGrid *grid;
			bool initDone = false;
	};

}

#endif /* SRC_CLIENT_WORLD_H_ */
