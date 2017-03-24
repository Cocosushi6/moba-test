#include "renderer.h"

//OpenGL headers TODO
Rendering::Renderer::Renderer(World::GameMap *map, Objects::GameEntityManager *manager) {
    this->map = map;
    this->manager = manager;
    init();
}

Rendering::Renderer::addEntityModel(int id, Model *model) {
        entityModels[id] = model;
}

