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
			void removeClient(int id);
			Game* getAttachedGame();
			DataManager::ClientManager* getClientManager();
			void poll();
		private:
			DataManager::InputManager m_inputManager;
			DataManager::ClientManager m_clientManager;
			DataManager::PacketParser m_packetParser;
			sf::SocketSelector sockSelector;
			sf::UdpSocket m_udpSocket;
			sf::TcpListener m_listener;
			int m_tcpPort, m_udpPort;
			Game *m_game;
			bool running = true;
	};

	class Client {
		public:
			Client();
			Client(const Client &copy, int port);
			Client(int id, int udpPort, sf::IpAddress address, tcp_sock_ptr tcpSocket, bool ready = false);
			tcp_sock_ptr getOutputSocket() { return m_tcpSocket; }//impl
			int getId() { return m_id; }//impl
			sf::IpAddress getIpAddress() { return m_address; }
			int getUDPPort() { return udpPort; }
		private:
			tcp_sock_ptr m_tcpSocket;
			int udpPort;
			int m_id;
			sf::IpAddress m_address;
			bool ready = false;
	};
}

#endif /* SRC_SERVER_NET_SERVER_H_ */
