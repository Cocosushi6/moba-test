#include "renderer.h"

//OpenGL headers TODO
Rendering::Renderer::Renderer(sf::Window *window, World::GameMap *map, Game *game) {
    this->window = window;
	this->map = map;
    this->manager = game->getEntityManager();
    this->init();
}

void Rendering::Renderer::renderMap() {

}

void Rendering::Renderer::init() {

}

void Rendering::Renderer::addEntityModel(int id, Model *model) {
        entityModels[id] = model;
}

