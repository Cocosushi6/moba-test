#include "server.h"
#include "../../common/consts.h"

#include "../game/game.h"

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

void Net::Server::waitForClient() {
	while(true) {
		if(m_listener.accept(m_tcpSocket) != Socket::Done) {
			cout << "Error happened during client connection. skipping. " << endl;
			return;
		}

		Net::Client client(this->m_clientManager.giveId(), m_tcpSocket, m_tcpSocket.getRemoteAddress());
		this->m_clientManager.addClient(client);
		Packet worldState;
		worldState << "INIT" << *game;
		this->sendTCPPacket(client.getId(), worldState);
	}
}

int Net::Server::sendTCPPacket(int clientID, Packet packet) {
	TcpSocket *out = this->m_clientManager.getClient(clientID).getOutputSocket();

	if(out->send(packet) != Socket::Done) {
		cout << "Error while sending TCP packet to client with id " << clientID << endl;
		return SRV_SEND_TCP_FAIL;
	}
	return 0;
}

int Net::Server::sendUDPPacket(int clientID, Packet packet) {
	IpAddress recipient = this->m_clientManager.getClient(clientID).getOutputSocket()->getRemoteAddress();

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

int DataManager::ClientManager::giveId() {
	do {
		m_lastID++;
	} while(std::find(m_ids.begin(), m_ids.end(), m_lastID) != m_ids.end()); //check if new id isn't already taken
	return m_lastID;
}

DataManager::PacketParser::PacketParser(Server *server, InputManager *iManager, ClientManager *cManager) :
		m_server(server), m_iManager(iManager), m_cManager(cManager) {

}

int DataManager::PacketParser::parsePacket(Packet packet, int clientID) {
	String descriptor;
	if(!(packet >> descriptor)) {
		cout << "Wrong packet format : no descriptor string at the beginning. Discarding packet." << endl;
		return -1;
	}

	//parse actual information
	if(descriptor == "INPUT") {
		InputState state;
		if(!packet >> state) {
			cout << "Error reading InputState, discarding packet" << endl;
			return -1;
		}
		this->m_iManager->parseInput(state);
	}

	return 0;
}


