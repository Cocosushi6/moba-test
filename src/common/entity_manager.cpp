#include "entity_manager.h"
#include "objects/object.h"
#include "objects/entities/entity.h"

#include <iostream>
#include <vector>
#include <map>

using namespace Objects;
using namespace std;

Objects::GameEntityManager::GameEntityManager(int lastID) : lastID(lastID) {}

Objects::GameEntityManager::~GameEntityManager() {
	for(map<int, Entities::Entity*>::iterator it = entities.begin(); it != entities.end(); it++) {
		removeEntity(it->first);
	}
	for(map<int, Objects::Object*>::iterator it = objects.begin(); it != objects.end(); it++) {
		removeObject(it->first);
	}
}

int GameEntityManager::attribID() {
	while(std::find(ids.begin(), ids.end(), lastID) != ids.end()) {
		lastID++;
	}
	ids.push_back(lastID);
	return lastID;
}

void GameEntityManager::addEntity(int id, Entities::Entity* ent) {
	entities[id] = ent;
	objects[id] = ent;
}

Entities::Entity* GameEntityManager::getEntity(int id) throw (std::string) {
	map<int, Entities::Entity*>::iterator it = entities.find(id);
	if(it != entities.end()) {
		return it->second; //returns the value (it->first is the key)
	}

	throw "No such entity with id " + id;
}

void GameEntityManager::addObject(int id, Object* obj) {
	objects[id] = obj;
}

Object* GameEntityManager::getObject(int id) throw (std::string) {
	map<int, Object*>::iterator it = objects.find(id);
	if(it != objects.end()) {
		return it->second; //returns the value (it->first is the key)
	}

	throw "No such object with id " + id;
}

//removes only the objects
void GameEntityManager::removeObject(int id) {
	delete objects[id];
	objects.erase(id);

	std::vector<int>::iterator idsIt = std::find(ids.begin(), ids.end(), id);
	if(idsIt != ids.end()) ids.erase(idsIt);
}

void GameEntityManager::removeEntity(int id) {
	removeObject(id);
	delete entities[id];
	entities.erase(id);
}
