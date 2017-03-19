#ifndef SRC_CLIENT_NET_PACKET_H_
#define SRC_CLIENT_NET_PACKET_H_


namespace GamePacket {

	class PacketParser {
		public:
			PacketParser(Game *game);
			int parse(sf::Packet packet);
			~PacketParser();
		private:
			Game* game;
	};
}




#endif /* SRC_CLIENT_NET_PACKET_H_ */
