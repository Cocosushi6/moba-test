#ifndef SRC_CLIENT_WORLD_H_
#define SRC_CLIENT_WORLD_H_

#include <string>
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>

#include "pugixml.hpp"

namespace World {
	class GameMap;

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
			explicit MapGrid(GameMap *map); //load this one by getting Map's pathToTmx file with getter
			explicit MapGrid(std::string data, GameMap *map);
			int parseMap();
		private:
			GameMap *map;
			int generateTiles();
			pugi::xml_document tmxFile;
			std::vector<std::vector<Tile>> tiles;
	};

	class GameMap {
		public:
			explicit GameMap();
			explicit GameMap(std::string pathToTmxFile);
			explicit GameMap(MapGrid data);
		private:
			std::string path;
			MapGrid *grid;
			bool initDone = false;
	};

}

sf::Packet& operator<<(sf::Packet& packet, const World::GameMap& game);
sf::Packet& operator>>(sf::Packet& packet, World::GameMap& state);

#endif /* SRC_CLIENT_WORLD_H_ */
