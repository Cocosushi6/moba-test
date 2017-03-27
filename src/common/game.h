#include <iostream>
#include "SFML/Network.hpp"
#include "../common/objects/object.h"
#include "../common/map/world.h"

class Game {
	public:
		Game(bool remote, World::GameMap map);
		~Game();
		void init();
		bool isRemote();
		Objects::GameEntityManager getEntityManager();
		World::GameMap getMap();
	private:
		//Remote is true if the game is located in a client instance, and is false if the game is located in a server instance (game is then local)
		bool remote = true;
		bool initDone = false;
		World::GameMap map;
		Objects::GameEntityManager entityManager;
};
