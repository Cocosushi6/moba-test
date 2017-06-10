#include <iostream>
#include "game.h"
#include "map/world.h"
#include "utils.h"
#include <string>

Game::Game() {
	this->map = new World::GameMap();
	this->entityManager = new Objects::GameEntityManager();
}

Game::Game(bool remote, std::string pathToMapFile) {
	this->map = new World::GameMap(remote, pathToMapFile);
	this->entityManager = new Objects::GameEntityManager();
}

Game::~Game() {
	delete map;
	delete entityManager;
}

void Game::init() {
	initDone = true;
}

bool Game::isInitDone() const {
	return initDone;
}

bool Game::isRemote() const {
	return remote;
}

Objects::GameEntityManager* Game::getEntityManager() const {
	return this->entityManager;
}

World::GameMap* Game::getMap() {
	return this->map;
}

void Game::printData() {
	for(std::vector<World::Tile> line : map->getMapGrid()->getTiles()) {
		for(World::Tile tile : line) {
			std::cout << "Tile " << tile.getUniqueID() << ": "  << tile.getWorldPosition().x << ", y : " << tile.getWorldPosition().y << ", Quad : " << std::endl;
			printQuad(tile.getCoordinates());
			std::cout << std::endl;
		}
	}
}

sf::Packet& operator<<(sf::Packet& packet, Game& game) {
	World::GameMap *map = game.getMap();
	return packet << *map;
}

sf::Packet& operator>>(sf::Packet& packet, Game& game) {
	World::GameMap *map = game.getMap();
	return packet >> *map;
}

GameInputManager::GameInputManager(Game *game) : attachedGame(game) {}

int GameInputManager::parseInput(InputState input, int entityID) {
	Objects::Entities::Entity *entity = attachedGame->getEntityManager()->getEntity(entityID);

	if(input.state) {

	}

}
