#include "renderer.h"
#include "ui/ui_manager.h"
#include "ui/ui_components.h"

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

//OpenGL headers TODO
Rendering::Renderer::Renderer(sf::RenderWindow *window, Game *game)
	: window(window), game(game) {
	this->uiManager = new UI::UIManager(this);
    this->init();
}

Rendering::Renderer::~Renderer() {
	delete uiManager;
}

void Rendering::Renderer::renderMap() {
	World::GameMap* map = game->getMap();
	
}

void Rendering::Renderer::init() {
	//All models of all entities are loaded here with addEntityModel
}

void Rendering::Renderer::addEntityModel(int id, Model *model) {
        entityModels[id] = model;
}

void Rendering::Renderer::drawLoadingScreen(std::string message) {
	sf::Font font;
	if(!font.loadFromFile("DejaVuSans.ttf")) {
		std::cout << "Couldn't load basic font DejaVuSans.ttf. Things will soon get ugly around here. " << std::endl;
		return;
	}

	sf::Text text;
	text.setFont(font);
	text.setString(message);
	text.setCharacterSize(20);
	text.setColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	this->window->draw(text);
	this->window->display();
}

//method to be called in while loop
void Rendering::Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT);

	//Do OGL rendering here
	this->renderMap();

	this->window->pushGLStates();

	this->uiManager->renderUI();

	this->window->popGLStates();

	this->window->display();
}
