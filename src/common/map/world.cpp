#include "world.h"
#include "../utils.h"
#include "pugixml.hpp"
#include <fstream>

using namespace std;
using namespace World;


Tile::Tile(int x, int y, int layerZ,  TileType type, Quad verticesCoordinates, int uniqueID, int size, bool solid) :
	layerZ(layerZ), type(type), verticesCoordinates(verticesCoordinates), uniqueID(uniqueID), size(size), solid(solid) {
	worldPosition.x = x;
	worldPosition.y = y;
}

Tile::Tile() {}

TileType Tile::getTileType() {
	return this->type;
}

bool Tile::isSolid() {
	return this->solid;
}

sf::Vector2<int> Tile::getWorldPosition() {
	return this->worldPosition;
}

Quad Tile::getCoordinates() {
	return this->verticesCoordinates;
}

int Tile::getUniqueID() {
	return this->uniqueID;
}

int Tile::getLayerZ() {
	return this->layerZ;
}

int Tile::getSize() {
	return this->size;
}

void World::Tile::setLayerZ(int layerZ) {
	this->layerZ = layerZ;
}

void World::Tile::setSize(int size) {
	this->size = size;
}

void World::Tile::setType(TileType type) {
	this->type = type;
}

void World::Tile::setUniqueId(int uniqueId) {
	uniqueID = uniqueId;
}

void World::Tile::setVerticesCoordinates(const Quad& verticesCoordinates) {
	this->verticesCoordinates = verticesCoordinates;
}

void World::Tile::setWorldPosition(const sf::Vector2<int>& worldPosition) {
	this->worldPosition = worldPosition;
}

void World::Tile::setSolid(bool solid) {
	this->solid = solid;
}

GameMap::GameMap() {
	this->remote = true;
	this->grid = new MapGrid(this);
}

GameMap::GameMap(bool remote) : remote(remote) {
	this->grid = new MapGrid(this);
}

GameMap::GameMap(bool remote, string pathToGridFile) {
	this->path = pathToGridFile;
	this->grid = new MapGrid(this, 1);
}

GameMap::GameMap(bool remote, MapGrid data) {
	this->grid = grid;
}

std::string GameMap::getMapPath() {
	return this->path;
}

MapGrid* GameMap::getMapGrid() {
	return this->grid;
}

MapGrid::MapGrid(GameMap *map) : map(map) {
	this->layerNum = 0;
}

MapGrid::MapGrid(string data, GameMap *map, int layerNumber) : layerNum(layerNumber) {
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

MapGrid::MapGrid(GameMap *map, int layerNumber) : layerNum(layerNumber) {
	this->map = map;
	pugi::xml_parse_result result = tmxFile.load_file(map->getMapPath().c_str());
	if(result) {
		cout << "File parsed successfully. Generating tiles..." << endl;
		if(generateTiles() != 0) {
			cout << "Error while generating tiles" << endl;
		}
	} else {
		cout << "Error while parsing xml map file : " << map->getMapPath() << endl;
	}
}

int MapGrid::generateTiles() {
	ifstream objFile("map.obj"); //layer 1
	if(!objFile) {
		cout << "couldn't load obj file : error while opening file" << endl;
		return -2;
	}

	string line;
	int lastID = 0;
	vector<Vertex> vertices;
	std::map<int, Quad> idForQuad;

	while(getline(objFile, line)) {
		vector<string> lineData = split(line, ' ');
		if(lineData[0] == "v") {
			Vertex vertex;
			vertex.coordinates.x = std::stod(lineData[1].c_str());
			vertex.coordinates.y = std::stod(lineData[2].c_str());
			vertex.coordinates.z = std::stod(lineData[3].c_str());
			vertices.push_back(vertex);
		} else if(lineData[0] == "f") {
			Quad quad;
			for(int i = 0; i < 4; i++) {
				quad.vertices[i] = vertices[stoi(lineData[i+1])];
			}
			idForQuad[lastID] = quad;
			lastID++;
		}
	}

	pugi::xml_node data = tmxFile.child("map").child("layer").child("data");

	int tilewidth = tmxFile.child("map").child("tileset").attribute("tilewidth").as_int();
	int tileheight = tmxFile.child("map").child("tileset").attribute("tileheight").as_int();
	if(tilewidth != tileheight || tilewidth % 2 != 0) {
		cout << "Wrong tilewidth or tileheight values. They must be multiple of 2 and both equal" << endl;
		return -1;
	}

	pugi::string_t encoding = data.attribute("encoding").as_string();
	if(encoding != pugi::string_t("csv")) {
		cout << "Wrong map encoding " << data.attribute("encoding").as_string() << ", please use CSV instead. Aborting." << endl;
		return -1;
	}

	std::string rawCSVdata = data.child_value();
	std::vector<std::string> lines = split(rawCSVdata, '\n');
	int x = 0;
	int y = 0;

	lastID = 0;
	for(std::string line : lines) {
		//the tile numbers for a single line
		std::vector<std::string> tiles = split(line, ',');
		//The list of a line's tiles, once converted
		std::vector<Tile> resultLine;


		for(std::string tile : tiles) {
			//get tile type
			int tileNum = std::stoi(tile); //stoi = string to int
			//convert int to TileType
			TileType type = (TileType)tileNum;

			//create and add tile
			Tile t(x, y, 0, type, idForQuad[lastID], lastID);
			resultLine.push_back(t);

			//increment for next tile
			x += tilewidth;
			lastID++;
		}
		//add the line to the final array
		this->tiles.push_back(resultLine);

		for(vector<Tile> line : this->tiles) {
			for(Tile tile : line) {
				cout << "Tile " << tile.getUniqueID() << ": "  << tile.getWorldPosition().x << ", y : " << tile.getWorldPosition().y << ", Quad : " << endl;
				printQuad(tile.getCoordinates());
				cout << endl;
			}
		}

		//increment for next line
		x = 0;
		y += tileheight;
	}

	objFile.close();
	return 0;
}

std::vector<std::vector<World::Tile>> World::MapGrid::getTiles() {
	return tiles;
}

int World::MapGrid::getLayer() {
	return this->layerNum;
}

void World::MapGrid::setTiles(vector<vector<Tile>> tiles) {
	this->tiles = tiles;
}

void World::MapGrid::setLayer(int layer) {
	this->layerNum = layer;
}

sf::Packet& operator<<(sf::Packet& packet, const TileType& type) {
	return packet << (sf::Uint16)type;
}

sf::Packet& operator>>(sf::Packet& packet, TileType& type) {
	sf::Uint16 typeNumber;
	packet >> typeNumber;
	type = (TileType)typeNumber;
	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, World::Tile& tile) {
	return packet << tile.getWorldPosition() << (sf::Uint16)tile.getLayerZ() << (sf::Uint16)tile.getSize() << tile.isSolid() << tile.getTileType() << (sf::Uint32)tile.getUniqueID() << tile.getCoordinates();
}

sf::Packet& operator>>(sf::Packet& packet, World::Tile& tile) {
	sf::Vector2<int> worldPos;
	sf::Uint16 layerZ;
	sf::Uint16 size;
	bool solid;
	TileType type;
	sf::Uint32 uniqueID;
	Quad coordinates;
	packet >> worldPos >> layerZ >> size >> solid >> type >> uniqueID >> coordinates;
	tile.setWorldPosition(worldPos);
	tile.setLayerZ(layerZ);
	tile.setSize(size);
	tile.setSolid(solid);
	tile.setType(type);
	tile.setUniqueId(uniqueID);
	tile.setVerticesCoordinates(coordinates);
	if(!packet) {
		cout << "Packet error : Tile deserialization" << endl;
	}

	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, World::MapGrid& grid) {
	sf::Uint16 gridHeight = grid.getTiles().size(); //number of vectors (lines)
	packet << gridHeight;

	for(std::vector<World::Tile> line : grid.getTiles()) {
		sf::Uint16 lineWidth = line.size();
		packet << lineWidth;

		for(Tile t : line) {
			packet << t;
		}
	}

	packet << (sf::Uint16)grid.getLayer();
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, World::MapGrid& grid) {
	std::vector<std::vector<World::Tile>> tiles;

	sf::Uint16 gridHeight;
	packet >> gridHeight;

	for(int i = 0; i < gridHeight; i++) {
		sf::Uint16 lineWidth;
		packet >> lineWidth;

		std::vector<Tile> line(lineWidth);

		for(int i = 0; i < lineWidth; i++) {
			Tile t;
			packet >> t;

			line[i] = t;
		}

		tiles.push_back(line);
	}
	sf::Uint16 layer;
	packet >> layer;

	if(!packet) {
		cout << "Packet error : MapGrid deserialization" << endl;
	}

	grid.setLayer(layer);
	grid.setTiles(tiles);
	return packet;
}

sf::Packet& operator<<(sf::Packet& packet,  World::GameMap& map) {
	World::MapGrid* grid = map.getMapGrid();
	return packet << *grid;
}

sf::Packet& operator>>(sf::Packet& packet, World::GameMap& map) {
	World::MapGrid* grid = map.getMapGrid();
	return packet >> *grid;
}


