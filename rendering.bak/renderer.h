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
#include "utils/utils.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

int printOglErrors(char* file, int line);

namespace Rendering {

	//forward declaration
	namespace UI { class UIManager; }

	class Renderer {
		public:
			Renderer(sf::RenderWindow *window, Game *game);
			~Renderer();
			void render();
			void drawLoadingScreen(std::string message);
		private:
			void addShader(std::string name, Shader shad);
			void init();
			void renderUI();
			void renderMap();
			void renderObjects();
			void renderEntities();
			void addEntityModel(int id, Model *model);
		    void renderEntity(Objects::Entities::Entity *ent);
		    UI::UIManager *uiManager;
			sf::RenderWindow *window;
			Game *game;
			Model map; //model for the map
			std::map<int, Model*> entityModels;
			std::map<std::string, Shader*> shaders;
	};
		
}

#endif /* SRC_CLIENT_RENDERING_RENDERER_H_ */
