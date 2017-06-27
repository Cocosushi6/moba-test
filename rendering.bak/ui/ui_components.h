/*
 * ui_components.h
 *
 *  Created on: Apr 12, 2017
 *      Author: sacha
 */

#ifndef SRC_CLIENT_RENDERING_UI_UI_COMPONENTS_H_
#define SRC_CLIENT_RENDERING_UI_UI_COMPONENTS_H_

#include <SFML/Window.hpp>

namespace Rendering {
	namespace UI {
		class UIManager;

		class Component {
			public:
				Component(UIManager *manager);
				virtual ~Component();
				virtual void handleEvent(sf::Event *event) = 0;
			private:
				//TODO UI components
		};

	}
}



#endif /* SRC_CLIENT_RENDERING_UI_UI_COMPONENTS_H_ */
