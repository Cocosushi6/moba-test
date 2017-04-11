/*
 * renderer.h
 *
 *  Created on: Mar 19, 2017
 *      Author: sacha
 */

#ifndef SRC_CLIENT_RENDERING_RENDERER_H_
#define SRC_CLIENT_RENDERING_RENDERER_H_

#include "model.h"
#include "../../common/objects/object.h"
#include "../../common/objects/entities/entity.h"
#include "../../common/game.h"
#include <SFML/Window.hpp>
#include <map>

namespace Rendering {

	class Renderer {
		public:
			Renderer(sf::Window *window, Game *game);
			void renderMap();
			void renderObjects();
		private:
			void init();
			void addEntityModel(int id, Model *model);
		    void renderEntity(Objects::Entities::Entity *ent);

			sf::Window *window;
			Game *game;
			std::map<int, Model*> entityModels;
	};
		
}




#endif /* SRC_CLIENT_RENDERING_RENDERER_H_ */
