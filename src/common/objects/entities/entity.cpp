#include "entity.h"
#include "../object.h"

Objects::Entities::Entity::Entity(float mapX, float mapY, int layerZ, std::string name, GameEntityManager *entManager, World::GameMap *map, bool remote) : Objects::Object(mapX, mapY, layerZ, name, entManager, map, remote) {

}

void Objects::Entities::Entity::update(long tickrate) {
	float speed = tickrate * velocity;

	if(moving && (newX != this->mapX || newY != this->mapY)) {
		step(speed);
	}
}

void Objects::Entities::Entity::step(float speed) {

}
