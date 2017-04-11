#ifndef SRC_SERVER_NET_SERVER_H_
#define SRC_SERVER_NET_SERVER_H_

#include <vector>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>

#include "../../common/game.h"
#include "../../common/utils.h"
#include "data_manager.h"

namespace Net {
	class Server {
		public:
			Server(int tcpPort, int udpPort, Game *game); //impl
			int sendTCPPacket(int clientID, sf::Packet packet); //impl
			int sendUDPPacket(int clientID, sf::Packet packet); //impl
			int waitUDP();
			Game* getAttachedGame();
		private:
			void waitForClient();
			DataManager::InputManager m_inputManager;
			DataManager::ClientManager m_clientManager;
			DataManager::PacketParser m_packetParser;
			sf::UdpSocket m_udpSocket;
			sf::TcpSocket m_tcpSocket;
			sf::TcpListener m_listener;
			sf::Packet m_packet;
			int m_tcpPort, m_udpPort;
			Game *m_game;
	};

	class Client {
		public:
			Client();
			sf::TcpSocket* getOutputSocket() { return &m_socket; }//impl
			int getId() { return m_id; }//impl
			sf::IpAddress getIpAddress() { return m_address; }
		private:
			int m_id;
			sf::IpAddress m_address;
			sf::TcpSocket m_socket;
	};
}

#endif /* SRC_SERVER_NET_SERVER_H_ */
