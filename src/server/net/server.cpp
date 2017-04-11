#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "server.h"
#include "../../common/consts.h"
#include "../../common/utils.h"
#include "data_manager.h"

using namespace sf;
using namespace std;

Net::Server::Server(int tcpPort, int udpPort, Game *game)
: m_udpPort(udpPort), m_tcpPort(tcpPort), m_game(game), m_inputManager(this), m_clientManager(), m_packetParser(this, &m_inputManager, &m_clientManager) {


	if(m_listener.listen(tcpPort) != Socket::Done) {
		cout << "Failed to listen on port " << tcpPort << " ! Aborting. " << endl;
		return;
	}
	if(m_udpSocket.bind(DEFAULT_UDP_PORT) != Socket::Done) {
		cout << "Failed to bind udp port " << udpPort << " ! Aborting. " << endl;
		return;
	}

	Thread clientConnectionThread(&Net::Server::waitForClient, this);
	clientConnectionThread.launch();
}


void Net::Server::waitForClient() {
	while(true) {
		if(m_listener.accept(m_tcpSocket) != Socket::Done) {
			cout << "Error happened during client connection. skipping. " << endl;
			return;
		}


	}
}

int Net::Server::sendTCPPacket(int clientID, Packet packet) {
	TcpSocket *out = this->m_clientManager.getClient(clientID)->getOutputSocket();

	sf::Socket::Status status =  out->send(packet);
	if(status != Socket::Done) {
		cout << "Error while sending TCP packet to client with id " << clientID << endl;
		return SRV_SEND_TCP_FAIL;
	}
	return 0;
}

int Net::Server::sendUDPPacket(int clientID, Packet packet) {
	IpAddress recipient = this->m_clientManager.getClient(clientID)->getOutputSocket()->getRemoteAddress();

	if(packet.getDataSize() <= UdpSocket::MaxDatagramSize) {
		if(m_udpSocket.send(packet, recipient, DEFAULT_UDP_PORT) != Socket::Done) {
			cout << "Error while sending UDP data to " << recipient << ". " << endl;
			return SRV_SEND_UDP_FAIL;
		}
	} else {
		return SRV_SEND_UDP_TOO_LARGE;
	}

	return 0;
}

