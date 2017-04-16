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

int DataManager::InputManager::parseInput(InputState state) {

	return 0;
}

int DataManager::ClientManager::giveId() {
	do {
		m_lastID++;
	} while(std::find(m_ids.begin(), m_ids.end(), m_lastID) != m_ids.end()); //check if new id isn't already taken
	m_ids.push_back(m_lastID);
	return m_lastID;
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

	//Exception thrown if the user gives a nonsense id
	throw "No such id : " + id;
}

tcp_sock_ptr DataManager::ClientManager::getClientSocket(int id) throw (std::string) {
	std::map<int, tcp_sock_ptr>::iterator it = m_clientSockets.find(id);

	if(it != m_clientSockets.end()) {
		return it->second;
	}

	throw "No such id " + std::to_string(id) + " for a client socket. Maybe the user has disconnected ?";
}

void DataManager::ClientManager::setClientSocket(int id, tcp_sock_ptr socket) {
	tcp_sock_ptr socket_ptr(socket);
	m_clientSockets[id] = socket_ptr;
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

