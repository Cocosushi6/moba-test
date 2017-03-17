#ifndef CLIENT_H_
#define CLIENT_H_

#include "SFML/Network.hpp"

class Client {
	public:
		Client(sf::IpAddress address, int udpPort, int tcpPort);
		int connect();
	private:
		sf::UdpSocket udpSocket;
		sf::TcpSocket tcpSocket;
		int udpPort, tcpPort;
		sf::IpAddress serverAddress;
};

#endif /* CLIENT_H_ */
