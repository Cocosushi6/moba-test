
#ifndef SRC_DATAMANAGER_H
#define SRC_DATAMANAGER_H

#include <SFML/Network.hpp>
#include "../../common/utils.h"

using namespace sf;

namespace Net {
	class Server;
	class Client;
}

namespace DataManager {

	class InputManager {
		public:
			InputManager(Net::Server *server);
			int parseInput(InputState state); //TODO parse input manager
		private:
			Net::Server *server;
	};

	class ClientManager {
		public:
			ClientManager(int lastID = 0);
			std::vector<int> getIds();
			std::map<int, Net::Client*> getClients();
			Net::Client* getClient(int id) throw(std::string);
			int giveId(); //impl
			void addClient(Net::Client *client);
		private:
			std::map<int, Net::Client*> m_clients;
			std::vector<int> m_ids;
			int m_lastID;
	};

	class PacketParser {
		public:
			PacketParser(Net::Server *server, InputManager *iManager, ClientManager *cManager);
			int parsePacket(Packet packet, int clientID); //
		private:
			Net::Server *m_server;
			InputManager *m_iManager;
			ClientManager *m_cManager;
	};
}

#endif /* SRC_SERVER_NET_DATA_MANAGER_H_ */
