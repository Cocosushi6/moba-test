#ifndef CLIENT_H_
#define CLIENT_H_

#include "SFML/Network.hpp"
#include "packet.h"

class Client {
	public:
		Client(sf::IpAddress address, int udpPort, int tcpPort, GamePacket::PacketParser *parser);
		bool connect();
		int sendTCPPacket(sf::Packet packet);
		int sendUDPPacket(sf::Packet packet);
		void poll();
		void setServerAddress(sf::IpAddress address);
		int getLocalID();
		void setLocalID(int id);
	private:
		sf::UdpSocket udpSocket;
		sf::TcpSocket tcpSocket;
		int udpPort, tcpPort;
		sf::IpAddress serverAddress;
		sf::Packet dataPacket;
		GamePacket::PacketParser *packetParser;
		int idChanged = false; //To lock the id once it is changed for the first time
		int localID = -1;
};

#endif /* CLIENT_H_ */
