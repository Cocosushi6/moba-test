#include "renderer.h"

//OpenGL headers TODO
Rendering::Renderer::Renderer(sf::Window *window, Game *game)
	: window(window), game(game) {
    this->init();
}

void Rendering::Renderer::renderMap() {

}

void Rendering::Renderer::init() {

}

void Rendering::Renderer::addEntityModel(int id, Model *model) {
        entityModels[id] = model;
}

