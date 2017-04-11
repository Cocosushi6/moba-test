#ifndef SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_
#define SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_

#include <string>

#include "../object.h"
#include "../../map/world.h"

namespace Weapons {
	class Weapon;
}

class Game;

namespace Objects {

	namespace Entities {

		class Entity : public Object {
			public:
				Entity(float mapX, float mapY, int layerZ, std::string name, Game *game, bool remote);
				virtual void update(long tickrate) = 0;
				virtual void move(float mapX, float mapY, int layerZ) = 0; //sets newX, newY and newZ variables
				virtual ~Entity() = 0;
			protected:
				virtual void step(float speed) = 0;
				float newX = 0, newY = 0, newZ = 0;
				float angle = 0;
				float velocity = 0;
				bool moving = false;
		};

		//basic implementation of Entity
		class MovingEntity : public Entity {
			public:
				MovingEntity(float mapX, float mapY, int layerZ);
				void update();
				void move(float mapX, float mapY, int layerZ);
				~MovingEntity();
			private:
				void step(float speed);
		};

		class Player : public Entity {
			public:
				Player(float mapX, float mapY, int layerZ);
				void update();
				void move(float mapX, float mapY, int layerZ);
				void useWeapon();
				~Player();
			private:
				Weapons::Weapon *weapon;
		};

	}

}



#endif /* SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_ */
