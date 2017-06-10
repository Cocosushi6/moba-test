#include <iostream>
#include "object.h"
#include "../game.h"

using namespace std;

Objects::Object::Object(float mapX, float mapY, int heightZ, std::string name, Game *game, bool remote) {
	this->mapX = mapX;
	this->mapY = mapY;
	this->heightZ = heightZ;
	this->name = name;
	this->remote = remote;
	this->game = game;
}

Objects::Object::~Object() {
	delete game;
}

float Objects::Object::getBasicDamage() const {
	return basicDamage;
}

float Objects::Object::getDefense() const {
	return defense;
}

int Objects::Object::getHeightZ() const {
	return heightZ;
}

float Objects::Object::getLife() const {
	return life;
}

float Objects::Object::getMana() const {
	return mana;
}

float Objects::Object::getMapX() const {
	return mapX;
}

float Objects::Object::getMapY() const {
	return mapY;
}

const std::string& Objects::Object::getName() const {
	return name;
}
