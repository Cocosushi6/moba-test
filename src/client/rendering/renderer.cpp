#include "renderer.h"
#include "ui/ui_manager.h"
#include "ui/ui_components.h"

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

}

void Rendering::Renderer::init() {
	//All models of all entities are loaded here with addEntityModel
}

void Rendering::Renderer::addEntityModel(int id, Model *model) {
        entityModels[id] = model;
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
