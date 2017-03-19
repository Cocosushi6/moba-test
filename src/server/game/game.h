#ifndef SRC_SERVER_GAME_GAME_H_
#define SRC_SERVER_GAME_GAME_H_

#include "../net/server.h"
#include "../../common/objects/object.h"

namespace Game {
	class Game {
		public:
			Game(Net::Server::Server *server);
			int addObject(Objects::Object *obj);
		private:


	};

	sf::Packet& operator<<(sf::Packet &packet, const Game& game) {

	}

	sf::Packet& operator>>(sf::Packet &packet, const Game& game) {

	}

	enum GameState {
		LOADING, RUNNING, DONE
	};
}

#endif /* SRC_SERVER_GAME_GAME_H_ */
