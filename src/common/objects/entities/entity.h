#ifndef SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_
#define SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_

#include "../object.h"

namespace Objects {

	namespace Entities {

		class Entity : public Object {
			public:
				Entity(float mapX, float mapY, int layerZ);
				virtual void update() = 0;
				virtual void move(float mapX, float mapY, int layerZ) = 0;
				virtual ~Entity();
			private:


		};

		//basic implementation of Entity
		class MovingEntity : public Entity {

		};

		class Player : public Entity {
			public:
				void update();
				void move(float mapX, mapY, int layerZ);
				void attack();
			private:


		};

	}

}



#endif /* SRC_COMMON_OBJECTS_ENTITIES_ENTITY_H_ */
