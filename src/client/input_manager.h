/*
 * input_manager.h
 *
 *  Created on: Jun 28, 2017
 *      Author: sacha
 */

#ifndef SRC_CLIENT_INPUT_MANAGER_H_
#define SRC_CLIENT_INPUT_MANAGER_H_

#include "../common/game.h"
#include "net/client.h"
#include <SFML/System.hpp>

class InputManager {
	public:
		InputManager(Game *game, Client *client, Rendering::Renderer *renderer);
		void processInput(sf::Time delta);
	private:
		void processLocalInput(sf::Time delta);
		void processRemoteInput(sf::Time delta);
		Game *game;
		Client *client;
		Rendering::Renderer *renderer;
};



#endif /* SRC_CLIENT_INPUT_MANAGER_H_ */
