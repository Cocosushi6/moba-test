#include "server.h"
#include "../../common/consts.h"

#include "../../common/game.h"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

Net::Server::Server(int tcpPort, int udpPort, Game::Game *game) : m_udpPort(udpPort), m_tcpPort(tcpPort), m_game(game) {
	if(m_listener.listen(tcpPort) != Socket::Done) {
		cout << "Failed to listen on port " << tcpPort << " ! Aborting. " << endl;
		return;
	}
	if(m_udpSocket.bind(DEFAULT_UDP_PORT) != Socket::Done) {
		cout << "Failed to bind udp port " << udpPort << " ! Aborting. " << endl;
		return;
	}

	this->m_inputManager();
	this->m_clientManager();
	this->m_packetParser(this, m_inputManager, m_clientManager);

	Thread clientConnectionThread(&waitForClient);
	clientConnectionThread.launch();
}

Net::Client::Client(int id, sf::TcpSocket socket, sf::IpAddress address) : m_id(id), m_socket(socket), m_address(address) {

}

void Net::Server::waitForClient() {
	while(true) {
		if(m_listener.accept(m_tcpSocket) != Socket::Done) {
			cout << "Error happened during client connection. skipping. " << endl;
			return;
		}

		Net::Client client(this->m_clientManager.giveId(), m_tcpSocket, m_tcpSocket.getRemoteAddress());
		this->m_clientManager.addClient(&client);
		Packet worldState;
		worldState << "INIT" << *game;
		this->sendTCPPacket(client.getId(), worldState);
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

