/*
 * input_manager.cpp
 *
 *  Created on: Jun 28, 2017
 *      Author: sacha
 */

#include "input_manager.h"
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;

InputManager::InputManager(Game *game, Client *client, Rendering::Renderer *renderer)
: game(game), client(client), renderer(renderer) {}

void InputManager::processInput(sf::Time delta) {
	processLocalInput(delta);
	processRemoteInput(delta);
}

void InputManager::processRemoteInput(sf::Time delta) {

}

void InputManager::processLocalInput(sf::Time delta) {
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		renderer->getCamera()->processKeyboard(CameraMovement::BACK, delta.asSeconds());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		renderer->getCamera()->processKeyboard(CameraMovement::FORWARD, delta.asSeconds());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		renderer->getCamera()->processKeyboard(CameraMovement::LEFT, delta.asSeconds());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		renderer->getCamera()->processKeyboard(CameraMovement::RIGHT, delta.asSeconds());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		renderer->getCamera()->processKeyboard(CameraMovement::UP, delta.asSeconds());
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		renderer->getCamera()->processKeyboard(CameraMovement::DOWN, delta.asSeconds());
	}
}



