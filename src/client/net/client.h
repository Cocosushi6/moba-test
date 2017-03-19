#ifndef CLIENT_H_
#define CLIENT_H_

#include "SFML/Network.hpp"
#include "packet.h"

class Client {
	public:
		Client(sf::IpAddress address, int udpPort, int tcpPort, GamePacket::PacketParser *parser);
		int connect();
		int sendTCPPacket(sf::Packet packet);
		int sendUDPPacket(sf::Packet packet);
		void poll();
	private:
		sf::UdpSocket udpSocket;
		sf::TcpSocket tcpSocket;
		int udpPort, tcpPort;
		sf::IpAddress serverAddress;
		sf::Packet dataPacket;
		GamePacket::PacketParser *packetParser;
};

#endif /* CLIENT_H_ */
