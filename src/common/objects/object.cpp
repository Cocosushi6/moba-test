#include <iostream>
#include "object.h"

Objects::Object::Object(float mapX, float mapY, int heightZ, std::string name, GameEntityManager *entManager, World::GameMap *map) {
	this->mapX = mapX;
	this->mapY = mapY;
	this->heightZ = heightZ;
	this->name = name;
	this->entManager = entManager;
	this->map = map;
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
