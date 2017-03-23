/*
 * renderer.h
 *
 *  Created on: Mar 19, 2017
 *      Author: sacha
 */

#ifndef SRC_CLIENT_RENDERING_RENDERER_H_
#define SRC_CLIENT_RENDERING_RENDERER_H_

#include "../../common/map/world.h"
#include "model.h"
#include "../../common/objects/object.h"

namespace Rendering {

	class Renderer {
		public:
			Renderer(World::GameMap *map, Objects::GameEntityManager *manager);
			void renderMap();
			void renderObjects();
		private:
			void initGL();
			void addEntityModel(int id, Model *model);
			
			World::GameMap *map;
			Objects::GameEntityManager *manager;
			std::map<int, *Model> entityModels;
	};
	
		
}




#endif /* SRC_CLIENT_RENDERING_RENDERER_H_ */
