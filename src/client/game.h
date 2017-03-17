#include <iostream>
#include "../common/netutils/netutils.h"
#include "scene/world.h"
#include "SFML/Network.hpp"

using namespace sf;

class Game {
	public:
		Game();
		~Game();
		init();
	private:
		World::Map *map;
};
