#include <iostream>
#include "object.h"
#include "../game.h"

using namespace std;

Objects::Object::Object(float mapX, float mapY, float mapZ, int heightZ, std::string name, Game *game, bool remote)
: mapX(mapX), mapY(mapY), mapZ(mapZ), heightZ(heightZ), name(name), game(game), remote(remote) {
}

Objects::Object::~Object() {
	delete game;
}

int Objects::Object::getHeightZ() const {
	return heightZ;
}

float Objects::Object::getMapX() const {
	return mapX;
}

float Objects::Object::getMapY() const {
	return mapY;
}

float Objects::Object::getMapZ() const {
	return mapZ;
}

std::string& Objects::Object::getName() const {
	return name;
}

void Objects::Object::setHeightZ(int heightZ) {
	this->heightZ = heightZ;
}

void Objects::Object::setMapX(float mapX) {
	this->mapX = mapX;
}

void Objects::Object::setMapY(float mapY) {
	this->mapY = mapY;
}

void Objects::Object::setMapZ(float mapZ) {
	this->mapZ = mapZ;
}

void Objects::Object::setName(std::string& name) {
	this->name = name;
}

sf::Packet& operator<<(sf::Packet& packet, Objects::Object &obj) {
	return packet << obj.getMapX() << obj.getMapY() << obj.getMapZ() << obj.getHeightZ() << obj.getName();
}

sf::Packet& operator>>(sf::Packet& packet, Objects::Object &obj) {
	float mapX, mapY, mapZ;
	int heightZ;
	std::string name;
	packet >> mapX >> mapY >> mapZ >> heightZ >> name;
	obj.setHeightZ(heightZ);
	obj.setMapX(mapX);
	obj.setMapY(mapY);
	obj.setMapZ(mapZ);
	obj.setName(name);
	return packet;
}


