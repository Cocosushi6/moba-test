#ifndef SRC_COMMON_OBJECTS_OBJECT_H_
#define SRC_COMMON_OBJECTS_OBJECT_H_

#include <string>
#include <iostream>
#include <vector>
#include "entities/entity.h"
#include "../map/world.h"

namespace Objects {
	class Object {
		public:
			Object(float mapX, float mapY, int heightZ, std::string name, GameEntityManager *entManager, World::GameMap *map, bool remote);
			virtual void update(long tickrate) = 0; //pure virtual method, Object is an abstract class
			virtual ~Object();
			float getBasicDamage() const;
			float getDefense() const;
			int getHeightZ() const;
			float getLife() const;
			float getMana() const;
			float getMapX() const;
			float getMapY() const;
			const std::string& getName() const;
		private:
			bool remote = false;
			float mapX, mapY;
			int heightZ;
			std::string name; //name is important : paths to 3D models are build according to this name
			float life = 10, defense = 10, mana = 0, basicDamage = 1;
			GameEntityManager *entManager;
			World::GameMap *map;
	};


	class GameEntityManager {
		public:
			void addEntity(int id, Entities::Entity* ent);
			Entities::Entity* getEntity(int id);
		private:
			std::map<int, Object> objects;
			std::map<int, Entities::Entity*> entities;
	};
}


#endif /* SRC_COMMON_OBJECTS_OBJECT_H_ */
