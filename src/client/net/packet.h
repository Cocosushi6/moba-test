#ifndef SRC_CLIENT_NET_PACKET_H_
#define SRC_CLIENT_NET_PACKET_H_

#include "../../common/map/world.h"
#include "../../common/game.h"

namespace GamePacket {

	class PacketParser {
		public:
			PacketParser(Game &game, World::GameMap &map);
			int parsePacket(sf::Packet packet);
			~PacketParser();
		private:
			Game *game;
			World::GameMap *map;
	};
}




#endif /* SRC_CLIENT_NET_PACKET_H_ */
