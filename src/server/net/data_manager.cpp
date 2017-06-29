#include "data_manager.h"
#include <iostream>
#include <SFML/Network.hpp>

#include "server.h"

using namespace sf;
using namespace std;

DataManager::InputManager::InputManager(Net::Server* server) :
		server(server) {

}

DataManager::ClientManager::ClientManager(int lastID) :
		m_lastID(lastID) {

}

DataManager::PacketParser::PacketParser(Net::Server *server, InputManager *iManager, ClientManager *cManager, Game *game) :
		m_server(server), m_iManager(iManager), m_cManager(cManager), game(game) {

}

int DataManager::InputManager::parseInput(InputState state, int clientID) {

	return 0;
}

int DataManager::ClientManager::giveId() {
	do {
		m_lastID++;
	} while(std::find(m_ids.begin(), m_ids.end(), m_lastID) != m_ids.end()); //check if new id isn't already taken
	m_ids.push_back(m_lastID);
	return m_lastID;
}

//Attribute an client to an id and store them;
void DataManager::ClientManager::addClient(client_ptr ptr) {
	int id = ptr->getId();
	this->m_clients[id] = ptr;
}

void DataManager::ClientManager::setClientForID(int id, client_ptr ptr) {
	this->m_clients[id] = ptr;
}

client_ptr DataManager::ClientManager::getClient(int id) throw (std::string) {

	std::map<int, client_ptr>::iterator it = m_clients.find(id);

	if (it != m_clients.end()) {
		return it->second;
	}

	//Exception thrown if the user gives a nonsense id
	throw "No such id : " + id;
}

std::map<int, client_ptr>& DataManager::ClientManager::getClients() {
	return m_clients;
}

std::vector<int> DataManager::ClientManager::getIds() {
	return this->m_ids;
}

int DataManager::PacketParser::parsePacket(Packet packet) {
	cout << "parsing packet" << endl;
	std::string descriptor = "";
	int clientID;
	if(!(packet >> descriptor)) {
		cout << "Wrong packet format : no descriptor string at the beginning. Dropping packet." << endl;
		return -1;
	}
	if(!(packet >> clientID)) {
		cout << "Wrong packet format : no ID at beginning of packet message after descriptor " << descriptor << endl;
		return -2;
	}
	cout << "found descriptor + clientID, parsing actual packet" << endl;
	//parse actual information
	if(descriptor == "INPUT") {
		InputState state;
		if(packet >> state) {
			int parseResult = this->m_iManager->parseInput(state, clientID);
			return parseResult;
		} else {
			cout << "Error while extracting packet" << endl;
			return -1;
		}
	} else if(descriptor == "INIT") {
		int port;
		if(packet >> port) {
			try {
				cout << "Initialising new client..." << endl;
				client_ptr currentClient = this->m_cManager->getClient(clientID);
				sf::IpAddress address = currentClient->getIpAddress();

				client_ptr newClient(new Net::Client(*currentClient, port));
				this->m_cManager->setClientForID(clientID, newClient);
				this->game->getEntityManager()->addEntity(clientID, new Objects::Entities::Player(0, 0, 0, 1, "player" + clientID, this->game, false));

				//new client is now initialised completely
				cout << "sending back game data to client..." << endl;
				sf::Packet worldState;
				worldState << "INIT" << *game;
				cout << "worldState packet data size : " << worldState.getDataSize() << endl;
				m_server->sendTCPPacket(clientID, worldState);
				cout << "game data sent back, client initialised successfully" << endl;
			} catch(std::string const& e) {
				cout << e << ", aborting." << endl;
				return -1;
			}
		} else {
			cout << "Error while fetching client port" << endl;
			this->m_cManager->removeClient(clientID);
			return -1;
		}
	}

	return 0;
}

void DataManager::ClientManager::removeClient(int id) {
	m_clients.erase(id);

	std::vector<int>::iterator idsIt = std::find(m_ids.begin(), m_ids.end(), id);
	if(idsIt != m_ids.end()) m_ids.erase(idsIt);
	cout << "DataManager.cpp : removed client with id " << id << endl;
}

