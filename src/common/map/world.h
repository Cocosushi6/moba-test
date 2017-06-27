#ifndef SRC_CLIENT_WORLD_H_
#define SRC_CLIENT_WORLD_H_

#include <string>
#include <iostream>
#include <vector>
#include <SFML/Network.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../utils.h"

#include "pugixml.hpp"

namespace World {
	class GameMap;

	class Tile {
		public:
			Tile(int x, int y, int layerZ, std::string type, Quad verticesCoordinates, int uniqueID, int size = 16, bool solid = false);
			Tile();
			Quad getCoordinates();
			sf::Vector2<int> getWorldPosition();
			void setSolid(bool solid);
			bool isSolid();
			std::string getTileType();
			int getUniqueID();
			int getLayerZ();
			int getSize();
			void setLayerZ(int layerZ);
			void setSize(int size = 16);
			void setType(std::string type);
			void setUniqueId(int uniqueId);
			void setVerticesCoordinates(const Quad& verticesCoordinates);
			void setWorldPosition(const sf::Vector2<int>& worldPosition);

		private:
			 //are ints because tiles are next to each other.
			//Z is the equivalent of heightZ or layerZ variables for entities
			//(and does not represent the OpenGL height)
			sf::Vector2<int> worldPosition;
			int layerZ;
			int size = 16;
			bool solid = false;
			std::string type;
			int uniqueID;
			Quad verticesCoordinates; //coordinates for every corner of the tile (for later calculations)
	};

	class MapGrid {
		public:
			explicit MapGrid(GameMap *map, int layerNumber); //load this one by getting Map's pathToTmx file with getter
			explicit MapGrid(std::string data, GameMap *map, int layerNumber);
			MapGrid(GameMap *map);
			~MapGrid();
			int parseMap();
			int getLayer();
			std::vector<std::vector<Tile>> getTiles();
			void setTiles(std::vector<std::vector<Tile>> tiles);
			void setLayer(int layer);
		private:
			int layerNum;
			GameMap *map;
			int generateTiles();
			pugi::xml_document tmxFile;
			std::vector<std::vector<Tile>> tiles;
	};

	class GameMap {
		public:
			explicit GameMap(bool remote);
			explicit GameMap(bool remote, std::string pathToTmxFile);
			explicit GameMap(bool remote, MapGrid data);
			GameMap(GameMap &map);
			GameMap();
			~GameMap();
			void registerTileType(std::string type);
			std::string intToTileType(int i);
			std::vector<std::string> getTileTypes();
			std::string getMapPath();
			MapGrid* getMapGrid();
			bool isRemote();
		private:
			void initBasicTileTypes();
			bool remote = false;
			std::string path;
			MapGrid *grid;
			bool initDone = false;
			std::vector<std::string> tileTypes;
	};

}

sf::Packet& operator<<(sf::Packet& packet,  World::MapGrid& grid);
sf::Packet& operator>>(sf::Packet& packet, World::MapGrid& grid);
sf::Packet& operator<<(sf::Packet& packet,  World::Tile& tile);
sf::Packet& operator>>(sf::Packet& packet, World::Tile& tile);
sf::Packet& operator<<(sf::Packet& packet,  World::GameMap& game);
sf::Packet& operator>>(sf::Packet& packet, World::GameMap& state);


#endif /* SRC_CLIENT_WORLD_H_ */
