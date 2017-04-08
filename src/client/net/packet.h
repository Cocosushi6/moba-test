#ifndef SRC_CLIENT_NET_PACKET_H_
#define SRC_CLIENT_NET_PACKET_H_

#include "../../common/map/world.h"
#include "../../common/game.h"
#include <SFML/Network.hpp>

namespace GamePacket {

	class PacketParser {
		public:
			PacketParser(Game *game);
			int parsePacket(sf::Packet packet);
			~PacketParser();
		private:
			Game *game;
			World::GameMap *map;
	};
}




#endif /* SRC_CLIENT_NET_PACKET_H_ */
