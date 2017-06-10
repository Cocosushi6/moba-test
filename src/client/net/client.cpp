#include <iostream>
#include <string>
#include <vector>

#include "client.h"
#include "packet.h"
#include "../../common/consts.h"

using namespace sf;
using namespace std;
using namespace GamePacket;

Client::Client(IpAddress address, int serverPort, GamePacket::PacketParser *parser) :
		serverAddress(address), packetParser(parser), serverPort(serverPort) {

}


bool Client::connect() {
	//connect TCP socket to server on port
	Socket::Status success = tcpSocket.connect(serverAddress, serverPort);
	if(success != Socket::Done) {
		std::cout << "Failed to connect tcp socket ! Aborting." << std::endl;
		return false;
	}
	if(udpSocket.bind(sf::Socket::AnyPort) != Socket::Done) {
		std::cout << "Failed to bind udp socket ! Aborting. " << std::endl;
		return false;
	}	
	this->udpPort = udpSocket.getLocalPort();
	this->connected = true;
	sf::Packet dataPacket;
	sf::Packet gamePacket;


	//Get localID for later communication with server
	if(tcpSocket.receive(dataPacket) != Socket::Done) {
		cout << "Error while receiving initialisation packet" << endl;
		return false;
	}
	string descriptor;
	if (!(dataPacket >> descriptor)) {
		cout << "No descriptor in packet, discarding" << endl;
		return false;
	}
	if(descriptor == "ID") {
		int id;
		if(!(dataPacket >> id)) {
			cout << "Failed to get ID from server ! aborting connection." << endl;
			return false;
		}
		if(id >= 0) {
			setLocalID(id);
		}
		cout << "Received ID from server. Sending back UDP port." << endl;

		Packet udpPortPacket;
		udpPortPacket << "INIT" << this->localID << udpPort;
		this->sendTCPPacket(udpPortPacket);
	}

	Game *localGame = packetParser->getGame();
	//Get actual game data
	if(tcpSocket.receive(gamePacket) != Socket::Done) {
		cout << "Error while receiving game data from server. Aborting. " << endl;
		return false;
	}
	gamePacket >> descriptor;
	if (descriptor == "INIT") {
		cout << "received init packet" << endl;
		Game newGame;
		Client::checkPacket(gamePacket);
		//TODO solve error here (not working)
		if (!(gamePacket >> newGame)) {
			cout << "Client.cpp : Error while deserializing game data and id at initialisation (PacketParser) " << endl;
			return false;
		}
		*localGame = newGame;
		localGame->printData();
		cout << "Game data received from server" << endl;
	} else {
		cout << "unknown descriptor " << descriptor << endl;
	}
	//then, set sockets to non blocking
	tcpSocket.setBlocking(false);
	udpSocket.setBlocking(false);

	cout << "connection done !" << endl;

	return true;
}

void Client::poll() {
	IpAddress sender;
	unsigned short senderPort;

	sf::Packet dataPacket;

	Socket::Status status = udpSocket.receive(dataPacket, sender, senderPort);
	if(status != Socket::Done && status != Socket::NotReady) {
		cout << "Error while receiving UDP packet, status : " << status << endl;
		if(status == Socket::Disconnected) {
			cout << "Disconnected from server, aborting." << endl;
			this->connected = false;
		}
	} else {
		if(status != Socket::NotReady) {
			cout << "udp packet received" << endl;
			packetParser->parsePacket(dataPacket);
		}
	}

	status = tcpSocket.receive(dataPacket);
	if(status != Socket::Done && status != Socket::NotReady) {
		cout << "Error while reading TCP packet, status : " << status << endl;
		if(status == Socket::Disconnected) {
			cout << "Disconnected from server, aborting. (status : 3)" << endl;
			this->connected = false;
		}
	} else {
		if(status != Socket::NotReady) {
			cout << "tcp packet received" << endl;
			packetParser->parsePacket(dataPacket);
		}
	}
}

int Client::sendTCPPacket(Packet packet) {
	sf::Socket::Status status = tcpSocket.send(packet);
	while(status == Socket::Partial) {
		status = tcpSocket.send(packet);
	}
	if(status != Socket::Done) {
		cout << "Error while sending TCP packet in client, state is : " << status << endl;
		return -1;
	}
	return 0;
}

int Client::sendUDPPacket(Packet packet) {
	if(udpSocket.send(packet, serverAddress, serverPort) != Socket::Done) {
		cout << "Error while sending UDP packet to server" << endl;
		return -1;
	}
	return 0;
}

void Client::setServerAddress(sf::IpAddress address) {
	serverAddress = address;
}

void Client::setLocalID(int id) {
	//ID can be changed only once
	if(!idChanged) {
		this->localID = id;
		idChanged = true;
	} else {
		cout << "ID already changed !!" << endl;
	}
}

bool Client::isConnected() {
	return this->connected;
}

int Client::getLocalID() {
	return this->localID;
}

bool Client::checkPacket(sf::Packet packet) {
	cout << "Packet size : " << packet.getDataSize() << endl;
	cout << "End of packet : " << std::boolalpha << packet.endOfPacket() << endl;
	if(packet) {
		return true;
	} else {
		return false;
	}
}
