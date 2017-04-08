#include "data_manager.h"

#include <iostream>
#include <SFML/Network.hpp>

using namespace sf;
using namespace std;

int DataManager::ClientManager::giveId() {
	do {
		m_lastID++;
	} while(std::find(m_ids.begin(), m_ids.end(), m_lastID) != m_ids.end()); //check if new id isn't already taken
	return m_lastID;
}

DataManager::PacketParser::PacketParser(Server *server, InputManager *iManager, ClientManager *cManager) :
		m_server(server), m_iManager(iManager), m_cManager(cManager) {

}

void DataManager::ClientManager::addClient(Net::Client *client) {
	int id = client->getId();
	this->m_clients[id] = client;
}

Net::Client* DataManager::ClientManager::getClient(int id) throw (std::string) {

	std::map<int, Net::Client*>::iterator it = m_clients.find(id);

	if (it != m_clients.end()) {
		return it->second;
	}

	throw "No such id : " + id;
}

std::map<int, Net::Client*> DataManager::ClientManager::getClients() {
	return this->m_clients;
}

std::vector<int> DataManager::ClientManager::getIds() {
	return this->m_ids;
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
		if(packet >> state) {
			int parseResult = this->m_iManager->parseInput(state);
			return parseResult;
		} else {
			cout << "Error while extracting packet" << endl;
			return -1;
		}
	}

	return 0;
}

