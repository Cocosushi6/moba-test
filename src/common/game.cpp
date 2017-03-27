#include <iostream>
#include "game.h"
#include <string>

Game::Game(bool remote, World::GameMap map) {
  this->map = map;
  this->remote = remote;
}

bool Game::isRemote() {
	return remote;
}

Objects::GameEntityManager Game::getEntityManager() {
	return entityManager;
}

World::GameMap getMap() {
    return this->map;
}