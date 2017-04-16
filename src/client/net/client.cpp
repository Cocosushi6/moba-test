#include <iostream>
#include <string>
#include <vector>

#include "client.h"
#include "packet.h"
#include "../../common/consts.h"

using namespace sf;
using namespace std;
using namespace GamePacket;

Client::Client(IpAddress address, int udpPort, int tcpPort, GamePacket::PacketParser *parser) : serverAddress(address), udpPort(udpPort), tcpPort(tcpPort), packetParser(parser) {

}


bool Client::connect() {
	//connect TCP socket to server on port
	Socket::Status success = tcpSocket.connect(serverAddress, udpPort);
	if(success != Socket::Done) {
		std::cout << "Failed to connect tcp socket ! Aborting." << std::endl;
		return false;
	}


	if(udpSocket.bind(tcpPort) != Socket::Done) {
		std::cout << "Failed to bind udp socket ! Aborting. " << std::endl;
		return false;
	}	
	
	//receive game data from server
	if(tcpSocket.receive(dataPacket) != Socket::Done) {
		cout << "Error while receiving initialisation packet" << endl;
		return false;
	}

	//Parse init packet and init game + localID
	{
		string descriptor;
		Game *localGame = packetParser->getGame();
		if (!(dataPacket >> descriptor)) {
			cout << "No descriptor in packet, discarding" << endl;
			return -1;
		}

		if (descriptor == "INIT") {
			Game newGame;
			int id;
			if (!(dataPacket >> id >> newGame)) {
				cout << "Error while deserializing game data and id at initialisation (PacketParser) " << endl;
				return -1;
			}
			*localGame = newGame;
			setLocalID(id);
		}
	}
	
	//then, set sockets to non blocking
	tcpSocket.setBlocking(false);
	udpSocket.setBlocking(false);

	return true;
}

void Client::poll() {
	IpAddress sender;
	unsigned short senderPort;
	if(udpSocket.receive(dataPacket, sender, senderPort) != (Socket::Done || Socket::NotReady)) {
		cout << "Error while receiving UDP packet" << endl;
	}
	packetParser->parsePacket(dataPacket);

	if(tcpSocket.receive(dataPacket) != (Socket::Done || Socket::NotReady)) {
		cout << "Error while reading TCP packet" << endl;
	}
	packetParser->parsePacket(dataPacket);
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
	if(udpSocket.send(packet, serverAddress, DEFAULT_UDP_PORT) != Socket::Done) {
		cout << "Error while sending UDP packet in client" << endl;
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
	}
}

int Client::getLocalID() {
	return this->localID;
}
