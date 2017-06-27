#include "world.h"
#include "../utils.h"
#include "pugixml.hpp"
#include <fstream>

using namespace std;
using namespace World;


Tile::Tile(int x, int y, int layerZ,  string type, Quad verticesCoordinates, int uniqueID, int size, bool solid) :
	layerZ(layerZ), type(type), verticesCoordinates(verticesCoordinates), uniqueID(uniqueID), size(size), solid(solid) {
	worldPosition.x = x;
	worldPosition.y = y;
}

Tile::Tile() {}

string Tile::getTileType() {
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

void World::Tile::setType(string type) {
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
	cout << "Creating game map" << endl;
	this->initBasicTileTypes();
	this->remote = true;
	this->grid = new MapGrid(this);
}

GameMap::GameMap(bool remote) : remote(remote) {
	this->initBasicTileTypes();
	this->grid = new MapGrid(this);
}

GameMap::GameMap(bool remote, string pathToGridFile) {
	this->initBasicTileTypes();
	this->path = pathToGridFile;
	this->grid = new MapGrid(this, 1);
}

GameMap::GameMap(bool remote, MapGrid data) {
	this->initBasicTileTypes();
	this->grid = grid;
}

GameMap::~GameMap() {
	delete grid;
}

void GameMap::initBasicTileTypes() {
	this->registerTileType("grass");
	this->registerTileType("grass");
	this->registerTileType("grass");
	this->registerTileType("grass");
	cout << "initialised basic tile types" << endl;
}

std::string GameMap::getMapPath() {
	return this->path;
}

MapGrid* GameMap::getMapGrid() {
	return this->grid;
}

bool GameMap::isRemote() {
	return this->remote;
}

MapGrid::MapGrid(GameMap *map) : map(map) {
	this->layerNum = 0;
}

MapGrid::~MapGrid() {

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
	cout << "Generating tiles" << endl;
	std::string mapPath;
	if(this->map->isRemote()) {
		mapPath = "map.obj";
	} else {
		mapPath = "map.obj";
	}

	ifstream objFile(mapPath); //layer 1
	if(!objFile) {
		cout << "couldn't load obj file : error while opening file" << endl;
		return -2;
	}

	string line;
	int lastID = 0;
	vector<sf::Vector3<double>> vertices;
	vector<sf::Vector3<double>> normals;
	vector<sf::Vector2<double>> texCoords;
	std::map<int, Quad> idForQuad;

	cout << "parsing obj file ..." << endl;

	while(getline(objFile, line)) {
		vector<string> lineData = split(line, ' ');
		//Vertex
		if(lineData[0] == "v") {
			sf::Vector3<double> vertex;
			vertex.x = std::stod(lineData[1].c_str());
			vertex.y = std::stod(lineData[2].c_str());
			vertex.z = std::stod(lineData[3].c_str());
			vertices.push_back(vertex);
		//Normals
		} else if(lineData[0] ==  "vn") {
			sf::Vector3<double> normal;
			normal.x = std::stod(lineData[1].c_str());
			normal.y = std::stod(lineData[2].c_str());
			normal.z = std::stod(lineData[3].c_str());
			normals.push_back(normal);
		} else if(lineData[0] == "vt") {
			sf::Vector2<double> texCoord;
			texCoord.x = std::stod(lineData[1].c_str());
			texCoord.y = std::stod(lineData[2].c_str());
			texCoords.push_back(texCoord);
		} else if(lineData[0] == "f") {
			Quad quad;
			for(int i = 0; i < 4; i++) {
				vector<string> vertData = split(lineData[i+1], '/');
				Vertex vert;
				vert.coordinates = vertices[stoi(vertData[0]) - 1];
				vert.textCoords = texCoords[stoi(vertData[1]) - 1];
				vert.normals = normals[stoi(vertData[2]) - 1];
				quad.vertices[i] = vert;
			}
			idForQuad[lastID] = quad;
			lastID++;
		}
	}


	//parse tmx file
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

	cout << "parsing tmx file ..." << endl;
	for(std::string line : lines) {
		//the tile numbers for a single line
		std::vector<std::string> tiles = split(line, ',');
		//The list of a line's tiles, once converted
		std::vector<Tile> resultLine;


		for(std::string tile : tiles) {
			//get tile type
			int tileNum = std::stoi(tile); //stoi = string to int
			//convert int to TileType
			std::string type = this->map->intToTileType(tileNum);
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

std::string World::GameMap::intToTileType(int num) {
	return tileTypes.at(num - 1);
}

void World::GameMap::registerTileType(string type) {
	tileTypes.push_back(type);
}

vector<string> World::GameMap::getTileTypes() {
	return this->tileTypes;
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


sf::Packet& operator<<(sf::Packet& packet, World::Tile& tile) {
	return packet << tile.getWorldPosition() << (sf::Uint16)tile.getLayerZ() << (sf::Uint16)tile.getSize() << tile.isSolid() << tile.getTileType() << (sf::Uint32)tile.getUniqueID() << tile.getCoordinates();
}

sf::Packet& operator>>(sf::Packet& packet, World::Tile& tile) {
	sf::Vector2<int> worldPos;
	sf::Uint16 layerZ;
	sf::Uint16 size;
	bool solid;
	string type;
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


