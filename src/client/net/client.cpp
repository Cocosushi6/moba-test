#include <iostream>
#include <string>
#include <vector>

#include "client.h"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

using namespace sf;
using namespace std;

Client::Client(IpAddress address, int udpPort, int tcpPort) : serverAddress(address), udpPort(udpPort), tcpPort(tcpPort) {

}

int Client::connect() {
	//connect TCP socket to server on port
	Socket::Status success = tcpSocket.connect(serverAddress, udpPort);
	if(success != Socket::Done) {
		std::cout << "Failed to connect tcp socket ! Aborting." << std::endl;
		return -1;
	}

	if(udpSocket.bind(tcpPort) != Socket::Done) {
		std::cout << "Failed to bind udp socket ! Aborting. " << std::endl;
		return -1;
	}

	return 0;
}
