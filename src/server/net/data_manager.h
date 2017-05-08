
#ifndef SRC_DATAMANAGER_H
#define SRC_DATAMANAGER_H

#include <SFML/Network.hpp>
#include <memory>
#include <iostream>

#include "../../common/utils.h"
#include "../../common/game.h"

using namespace sf;


namespace Net {
	class Server;
	class Client;
}

typedef std::shared_ptr<sf::TcpSocket> tcp_sock_ptr;
typedef std::shared_ptr<Net::Client> client_ptr;

namespace DataManager {

	class InputManager {
		public:
			InputManager(Net::Server *server);
			int parseInput(InputState state, int clientID); //TODO parse input manager
		private:
			Net::Server *server;
	};

	class ClientManager {
		public:
			ClientManager(int lastID = 0);
			std::vector<int> getIds();
			std::map<int, client_ptr> getClients();
			client_ptr getClient(int id) throw(std::string);
			int giveId(); //impl
			void addClient(client_ptr ptr);
			void removeClient(int id);
			void setClientForID(int id, client_ptr ptr);
		private:
			std::map<int, client_ptr> m_clients;
			std::vector<int> m_ids;
			int m_lastID;
	};

	class PacketParser {
		public:
			PacketParser(Net::Server *server, InputManager *iManager, ClientManager *cManager, Game* game);
			int parsePacket(Packet packet);
		private:
			Game *game;
			Net::Server *m_server;
			InputManager *m_iManager;
			ClientManager *m_cManager;
	};
}

#endif /* SRC_SERVER_NET_DATA_MANAGER_H_ */
