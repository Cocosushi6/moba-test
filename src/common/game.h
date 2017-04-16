#ifndef SRC_GAME_H
#define SRC_GAME_H

#include <iostream>
#include <SFML/Network.hpp>

#include "objects/object.h"
#include "entity_manager.h"
#include "map/world.h"

class Game {
	public:
		Game();
		Game(bool remote, std::string pathToMapFile);
		Game(bool remote, World::GameMap map);
		~Game();
		void init();
		bool isRemote() const;
		Objects::GameEntityManager* getEntityManager() const;
		World::GameMap* getMap() const;
	private:
		//Remote is true if the game is located in a client instance, and is false if the game is located in a server instance (game is then local)
		bool remote = true;
		bool initDone = false;
		World::GameMap *map = 0;
		Objects::GameEntityManager *entityManager = 0;
};

sf::Packet& operator<<(sf::Packet& packet, const Game& game);
sf::Packet& operator>>(sf::Packet& packet, Game& state);

#endif /* SRC_GAME_H */
