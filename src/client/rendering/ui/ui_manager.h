/*
 * ui_manager.h
 *
 *  Created on: Apr 12, 2017
 *      Author: sacha
 */

#ifndef SRC_CLIENT_RENDERING_UI_UI_MANAGER_H_
#define SRC_CLIENT_RENDERING_UI_UI_MANAGER_H_

#include <SFML/Window.hpp>

#include "../renderer.h"
#include "ui_components.h"
#include <map>
#include <string>

namespace Rendering {

	namespace UI {

		class UIManager {
			public:
				UIManager(Renderer *render);
				void renderUI();
				void handleEvent(sf::Event &event);
				void addComponent(Component* comp);
			private:
				std::map<std::string, Component*> components;
		};

	}

}



#endif /* SRC_CLIENT_RENDERING_UI_UI_MANAGER_H_ */
