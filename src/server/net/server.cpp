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
: m_udpPort(udpPort), m_tcpPort(tcpPort), m_game(game), m_inputManager(this), m_clientManager(), m_packetParser(this, &m_inputManager, &m_clientManager, game) {


	if(m_listener.listen(tcpPort) != Socket::Done) {
		cout << "Failed to listen on port " << tcpPort << " ! Aborting. " << endl;
		return;
	}
	if(m_udpSocket.bind(udpPort) != Socket::Done) {
		cout << "Failed to bind udp port " << udpPort << " ! Aborting. " << endl;
		return;
	}
	sockSelector.add(m_listener);
	sockSelector.add(m_udpSocket);
}

Net::Client::Client(int id, int port, sf::IpAddress address, tcp_sock_ptr tcpSocket, bool ready) :
		m_id(id), m_address(address), udpPort(port), m_tcpSocket(tcpSocket), ready(ready) {

}

Net::Client::Client(const Client &copy, int port) :
		m_id(copy.m_id), m_address(copy.m_address), udpPort(port), m_tcpSocket(copy.m_tcpSocket), ready(true) {

}

void Net::Server::poll() {
	while(running) {
		cout << "polling..." << endl;
		if(sockSelector.wait()) {
			if(sockSelector.isReady(m_listener)) {

				tcp_sock_ptr socket(new TcpSocket());
				Socket::Status status = m_listener.accept(*socket);

				if(status == Socket::Done) {
					//add client here, but mark it as not ready, as he has not given his port yet (full client initialisation happens when packet INIT is received
					//(see PacketParser in data_manager.cpp)
					int newID = m_game->getEntityManager()->attribID();
					client_ptr newClient(new Net::Client(newID, -1, socket->getRemoteAddress(), socket, false));
					m_clientManager.addClient(newClient);

					//send back its id
					Packet clientID;
					clientID << "ID" << newID;
					socket->send(clientID);

					sockSelector.add(*socket);
					cout << "Added new client ! ID : " << newID << endl;
				} else {
					cout << "Error while adding new Client ! Status : " << status << endl;
				}
			}
			for(std::map<int, client_ptr>::iterator it = m_clientManager.getClients().begin(); it != m_clientManager.getClients().end(); ++it) {
				Net::Client client = *it->second;
				sf::TcpSocket& sock = *client.getOutputSocket();
				if(sockSelector.isReady(sock)) {
					sf::Packet packet;
					Socket::Status status = sock.receive(packet);
					if(status == sf::Socket::Done) {
						cout << "DEBUG : parsing packet" << endl;
						this->m_packetParser.parsePacket(packet);
					} else {
						cout << "Error while receiving packet of client with id " << it->second->getId() << ", status is " << status << endl;
						if(status == Socket::Disconnected) {
							int discoID = it->second->getId();
							cout << "Player with id " << discoID << " was disconnected. " << endl;
							removeClient(discoID);
							sockSelector.remove(sock);
							cout << "removed all data concerning client with id " << discoID << endl;
							//bug with iterator (which loops again, even if m_clientManager.getClients() is empty), is avoided here (was segfaulting before)
							break;
						}
					}
				}
			}
			if(sockSelector.isReady(m_udpSocket)) {
				cout << "UDP socket ready" << endl;
				sf::IpAddress sender;
				unsigned short int port;
				sf::Packet packet;
				sf::Socket::Status status = m_udpSocket.receive(packet, sender, port);
				if(status != Socket::Done) {
					cout << "Error while receiving UDP packet from address " << sender << endl;
				} else {
					m_packetParser.parsePacket(packet);
				}
			}
		}
		cout << "done..." << endl;
	}
}

void Net::Server::removeClient(int id) {
	m_clientManager.removeClient(id);
	m_game->getEntityManager()->removeEntity(id);
	cout << "Net::Server::removeClient : removed client with id " << id << endl;
}

sf::Socket::Status receiveWithTimeout(sf::TcpSocket &socket, sf::Packet &packet, int timeout) {
	sf::SocketSelector selector;
	selector.add(socket);
	if(selector.wait(sf::seconds(timeout))) {
		return socket.receive(packet);
	} else {
		return sf::Socket::NotReady;
	}
}

int Net::Server::sendTCPPacket(int clientID, Packet packet) {
	tcp_sock_ptr out = this->m_clientManager.getClient(clientID)->getOutputSocket();

	sf::Socket::Status status =  out->send(packet);
	if(status != Socket::Done) {
		std::string str;
		if(status == Socket::Error) {
			str= "error";
		} else if(status == Socket::Disconnected) {
			str = "disconnected";
			this->m_clientManager.removeClient(clientID);
		} else if(status == Socket::NotReady) {
			str = "not ready";
		} else if(status == Socket::Partial) {
			str = "partial";
		}
		cout << "Error while sending TCP packet to client with id " << clientID << ". Socket status : " <<  str << endl;
		return SRV_SEND_TCP_FAIL;
	}
	return 0;
}

int Net::Server::sendUDPPacket(int clientID, Packet packet) {
	IpAddress recipient = this->m_clientManager.getClient(clientID)->getOutputSocket()->getRemoteAddress();
	int clientPort = this->m_clientManager.getClient(clientID)->getUDPPort();

	if(packet.getDataSize() <= UdpSocket::MaxDatagramSize) {
		if(m_udpSocket.send(packet, recipient, clientPort) != Socket::Done) {
			cout << "Error while sending UDP data to " << recipient << ". " << endl;
			return SRV_SEND_UDP_FAIL;
		}
	} else {
		return SRV_SEND_UDP_TOO_LARGE;
	}

	return 0;
}

