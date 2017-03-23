/*
 * renderer.h
 *
 *  Created on: Mar 19, 2017
 *      Author: sacha
 */

#ifndef SRC_CLIENT_RENDERING_RENDERER_H_
#define SRC_CLIENT_RENDERING_RENDERER_H_

#include "../../common/map/world.h"

namespace Rendering {

	class Renderer {
		public:
			Renderer();
			void renderMap(World::GameMap *map);
			void renderObjects();
		private:
			void initGL();
	};
	
		
}




#endif /* SRC_CLIENT_RENDERING_RENDERER_H_ */
