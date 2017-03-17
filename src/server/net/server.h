#ifndef SRC_SERVER_NET_SERVER_H_
#define SRC_SERVER_NET_SERVER_H_

#include "../../common/game/game.h"
#include "SFML/Network.hpp"
#include <vector>
#include <string>
#include <iostream>

using namespace sf;

namespace Net {
	class Server {
		public:
			Server(int tcpPort, int udpPort, Game::Game *game); //impl
			int sendTCPPacket(int clientID, Packet packet); //impl
			int sendUDPPacket(int clientID, Packet packet); //impl
			int waitUDP();
			Game* getAttachedGame() { return game; }//impl
		private:
			void waitForClient();
			DataManager::InputManager m_inputManager;
			UdpSocket m_udpSocket;
			TcpSocket m_tcpSocket;
			TcpListener m_listener;
			Packet m_packet;
			DataManager::ClientManager m_clientManager;
			DataManager::PacketParser m_packetParser;
			int m_tcpPort, m_udpPort;
			Game::Game *m_game;
	};

	class Client {
		public:
			Client(int id, TcpSocket socket, IpAddress address) : m_id(id), m_socket(socket), m_address(address) {}
			TcpSocket* getOutputSocket() { return &m_socket; }//impl
			int getId() { return m_id; }//impl
			IpAddress getIpAddress() { return m_address; }
		private:
			int m_id;
			IpAddress m_address;
			TcpSocket m_socket;
	};
}

using namespace Net;

namespace DataManager {

	class InputManager {
		public:
			InputManager(Server *server);
			int parseInput(InputState state); //TODO parse input manager
		private:

	};

	class ClientManager {
		public:
			ClientManager(int lastID = 0) : m_lastID(lastID) {}
			std::vector<int> getIds() { return m_ids; }//impl
			std::map<int, Net::Client> getClients() { return m_clients; } //impl

			Net::Client getClient(int id) throw(std::out_of_range){ //impl, bancal
				std::map<int, Net::Client>::iterator it = m_clients.find(id);
				if(it != m_clients.end()) {
					return it->second;
				}
				throw std::out_of_range;
			}
			int giveId(); //impl
			void addClient(Net::Client client) { //impl
				int id = client.getId();
				m_clients[id] = client;
			}
		private:
			std::map<int, Net::Client> m_clients;
			std::vector<int> m_ids;
			int m_lastID;
	};

	class PacketParser {
		public:
			PacketParser(Server *server, InputManager *iManager, ClientManager *cManager);
			int parsePacket(Packet packet, int clientID); //
		private:
			Server *m_server;
			InputManager *m_iManager;
			ClientManager *m_cManager;
	};
}

#endif /* SRC_SERVER_NET_SERVER_H_ */
