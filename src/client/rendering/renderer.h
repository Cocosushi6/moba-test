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
#include <SFML/Graphics.hpp>
#include <map>

namespace Rendering {
	//forward declaration
	namespace UI { class UIManager; }

	class Renderer {
		public:
			Renderer(sf::RenderWindow *window, Game *game);
			~Renderer();
			void render();
		private:
			void renderUI();
			void renderMap();
			void renderObjects();
			void renderEntities();
			void init();
			void addEntityModel(int id, Model *model);
		    void renderEntity(Objects::Entities::Entity *ent);
		    UI::UIManager *uiManager;
			sf::RenderWindow *window;
			Game *game;
			std::map<int, Model*> entityModels;
	};
		
}




#endif /* SRC_CLIENT_RENDERING_RENDERER_H_ */
