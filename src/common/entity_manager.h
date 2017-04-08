#ifndef SRC_COMMON_OBJECTS_ENTITY_MANAGER_H_
#define SRC_COMMON_OBJECTS_ENTITY_MANAGER_H_
#include <map>

#include "objects/object.h"
#include "objects/entities/entity.h"

namespace Objects {

	class GameEntityManager {
		public:
			void addEntity(int id, Entities::Entity* ent);
			Entities::Entity* getEntity(int id);
			void addObject(int id, Object *obj);
			Object* getObject(int id);
		private:
			std::map<int, Object*> objects;
			std::map<int, Entities::Entity*> entities;
	};

}

#endif /* SRC_COMMON_OBJECTS_ENTITY_MANAGER_H_ */
