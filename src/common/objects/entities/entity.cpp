#include "entity.h"

Objects::Entities::Entity::Entity(float mapX, float mapY, int layerZ, std::string name, GameEntityManager *entManager, World::GameMap *map, bool remote) : Object(mapX, mapY, layerZ, name, entManager, map, remote) {

}

void Objects::Entities::Entity::update(long tickrate) {
	float speed = tickrate * speed;

	if(moving && (newX != mapX || newY != mapY)) {
		step(speed);
	}
}

void Objects::Entities::Entity::step(float speed) {

}

