#include <iostream>
#include "game.h"
#include "map/world.h"
#include <string>

Game::Game() {}

//FIX THIS
Game::Game(bool remote, std::string pathToMapFile) {
	this->map = new World::GameMap(pathToMapFile);
	this->entityManager = new Objects::GameEntityManager();
}

Game::~Game() {
	delete map;
	delete entityManager;
}

bool Game::isRemote() const {
	return remote;
}

Objects::GameEntityManager* Game::getEntityManager() const {
	return this->entityManager;
}

World::GameMap* Game::getMap() const {
	return this->map;
}

sf::Packet& operator<<(sf::Packet& packet, const Game& game) {
	return packet << *game.getMap();
}

sf::Packet& operator>>(sf::Packet& packet, Game& state) {
	return packet;
}


