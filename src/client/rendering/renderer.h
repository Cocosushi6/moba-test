#ifndef SRC_CLIENT_RENDERING_RENDERER_H_
#define SRC_CLIENT_RENDERING_RENDERER_H_

#include <iostream>
#include <string>

#include "renderers/map_renderer.h"
#include "utils/shader.h"
#include "ui/ui_manager.h"
#include "ui/ui_components.h"
#include "../../common/game.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Window.hpp>

namespace Rendering {
	class MapRenderer;

	class Renderer {
		public:
			Renderer(sf::Window* window, Game* game);
			~Renderer();
			void addModel(std::string path); //TODO change type from void to something like Model, ObjectModel, something attached to an id/descriptor (but not void)
			void render();
			Camera* getCamera();
			glm::mat4 getProjectionMatrix();
		private:
			//methods
			std::map<std::string, Shader*> shaders;
			//std::vector<BasicRenderer> renderers //TODO see about that
			MapRenderer* mapRenderer;
			UI::UIManager* uiManager;
			sf::Window* window;
			Game* game;
			Camera* cam;

			//attributes
			int loadShader(std::string identifier, std::string vertPath, std::string fragPath);
			void renderObjects(); //TODO think about how objects will be rendered
	};
}

#endif /* SRC_CLIENT_RENDERING_RENDERER_H_ */
