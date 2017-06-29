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
				Entity(float mapX, float mapY, float mapZ, int layerZ, std::string name, Game *game, bool remote);
				virtual void update(long tickrate) = 0;
				virtual void move(float mapX, float mapY, float mapZ, int layerZ) = 0; //sets newX, newY and newZ variables
				virtual ~Entity() = 0;
				float getAngle() const;
				void setAngle(float angle = 0);
				int getLayerZ() const;
				void setLayerZ(int layerZ = 0);
				float getNewX() const;
				void setNewX(float newX = 0);
				float getNewY() const;
				void setNewY(float newY = 0);
				float getNewZ() const;
				void setNewZ(float newZ = 0);
				float getVelocity() const;
				void setVelocity(float velocity = 0);
			protected:
				float newX = 0, newY = 0, newZ = 0;
				int layerZ = 0;
				float orientation = 0;
				float velocity = 0;
		};

		//basic implementation of Entity
		class MovingEntity : public Entity {
			public:
				MovingEntity(float mapX, float mapY, float mapZ, int layerZ);
				void move(float mapX, float mapY, float mapZ, int layerZ);
				~MovingEntity();
			private:
		};

		class Player : public Entity {
			public:
				Player(float mapX, float mapY, float mapZ, int layerZ, std::string name, Game *game, bool remote);
				void move(float mapX, float mapY, float mapZ, int layerZ);
				void useWeapon();
				void setWeapon(Weapons::Weapon *weapon);
				~Player();
			protected:
				Weapons::Weapon *weapon = NULL;
		};

	}

}

sf::Packet& operator<<(sf::Packet& packet, Objects::Entities::Entity &ent);
sf::Packet& operator>>(sf::Packet& packet, Objects::Entities::Entity &ent);
sf::Packet& operator<<(sf::Packet& packet, Objects::Entities::Player &pla);
sf::Packet& operator>>(sf::Packet& packet, Objects::Entities::Player &pla);


#endif /* SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_ */
