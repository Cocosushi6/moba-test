#ifndef SRC_COMMON_OBJECTS_ENTITY_MANAGER_H_
#define SRC_COMMON_OBJECTS_ENTITY_MANAGER_H_
#include <map>

#include "objects/object.h"
#include "objects/entities/entity.h"

namespace Objects {

	class GameEntityManager {
		public:
			GameEntityManager(int lastID = 0);
			int attribID();
			void addEntity(int id, Entities::Entity* ent);
			Entities::Entity* getEntity(int id) throw (std::string);
			void addObject(int id, Object *obj);
			Object* getObject(int id) throw (std::string);
			std::vector<int> getIDs();
		private:
			std::map<int, Object*> objects;
			std::map<int, Entities::Entity*> entities;
			std::vector<int> ids;
			int lastID = 0;
	};

}

#endif /* SRC_COMMON_OBJECTS_ENTITY_MANAGER_H_ */
