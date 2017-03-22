#ifndef SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_
#define SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_

#include "../object.h"

namespace Objects {

	namespace Entities {

		class Entity : public Object {
			public:
				Entity(float mapX, float mapY, int layerZ, std::string name, GameEntityManager *entManager, World::GameMap *map);
				virtual void update() = 0;
				virtual void move(float mapX, float mapY, int layerZ) = 0;
				virtual ~Entity();
			private:
				float newX = 0, newY = 0, newZ = 0;
				float angle = 0;
				bool moving = false;
				World::GameMap *map;
		};

		//basic implementation of Entity
		class MovingEntity : public Entity {
			public:
				MovingEntity(float mapX, float mapY, int layerZ);
				void update();
				void move(float mapX, float mapY, int layerZ);
				~MovingEntity();
			private:

		};

		class Player : public Entity {
			public:
				void update();
				void move(float mapX, mapY, int layerZ);
				void useWeapon();
			private:
				
		};

	}

}



#endif /* SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_ */
