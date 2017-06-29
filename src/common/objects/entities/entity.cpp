#include "entity.h"
#include "../object.h"
#include "../../game.h"
#include "../../utils.h"
#include <cmath>

Objects::Entities::Entity::Entity(float mapX, float mapY, float mapZ, int layerZ, std::string name, Game *game, bool remote) : Objects::Object(mapX, mapY, mapZ, layerZ, name, game, remote) {

}

float Objects::Entities::Entity::getAngle() const {
	return orientation;
}

void Objects::Entities::Entity::setAngle(float orientation) {
	this->orientation = orientation;
}

int Objects::Entities::Entity::getLayerZ() const {
	return layerZ;
}

void Objects::Entities::Entity::setLayerZ(int layerZ ) {
	this->layerZ = layerZ;
}

float Objects::Entities::Entity::getNewX() const {
	return newX;
}

void Objects::Entities::Entity::setNewX(float newX ) {
	this->newX = newX;
}

float Objects::Entities::Entity::getNewY() const {
	return newY;
}

void Objects::Entities::Entity::setNewY(float newY ) {
	this->newY = newY;
}

float Objects::Entities::Entity::getNewZ() const {
	return newZ;
}

void Objects::Entities::Entity::setNewZ(float newZ ) {
	this->newZ = newZ;
}

float Objects::Entities::Entity::getVelocity() const {
	return velocity;
}

void Objects::Entities::Entity::setVelocity(float velocity ) {
	this->velocity = velocity;
}

Objects::Entities::Player::Player(float mapX, float mapY, float mapZ, int layerZ, std::string name, Game *game, bool remote) :
		Entity(mapX, mapY, mapZ, layerZ, name, game, remote) {

}

Objects::Entities::Entity::~Entity() {}

Objects::Entities::Player::~Player() {
	delete weapon;
}

void Objects::Entities::Player::move(float mapX, float mapY, float mapZ, int layerZ) {

}

void Objects::Entities::Player::update(long tickrate) {

}

