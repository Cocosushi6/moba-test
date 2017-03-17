#ifndef SRC_COMMON_OBJECTS_OBJECT_H_
#define SRC_COMMON_OBJECTS_OBJECT_H_

#include <string>
#include <iostream>
#include <vector>
#include "entities/entity.h"

namespace Objects {
	class Object {
		public:
			Object(int mapX, int mapY, int heightZ, std::string name, GameEntityManager *entManager);
			virtual void update() = 0; //pure virtual method, Object is an abstract class
			virtual ~Object();
		private:
			float mapX, mapY;
			int heightZ;
			std::string name;
			float life, defense, mana, basicDamage;
			GameEntityManager *entManager;
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
