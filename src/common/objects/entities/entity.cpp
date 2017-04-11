#include "entity.h"
#include "../object.h"
#include "../../game.h"

Objects::Entities::Entity::Entity(float mapX, float mapY, int layerZ, std::string name, Game *game, bool remote) : Objects::Object(mapX, mapY, layerZ, name, game, remote) {

}

