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
			cout << "Received ID from server. Sending back UDP port" << endl;

			Packet udpPortPacket;
			std::string desc = "INIT";
			udpPortPacket << desc << this->localID << udpPort;
			this->sendTCPPacket(udpPortPacket);


		} else if (descriptor == "INIT") {
			Game newGame;
			if (!(dataPacket >> newGame)) {
				cout << "Error while deserializing game data and id at initialisation (PacketParser) " << endl;
				return false;
			}
			*localGame = newGame;
			cout << "Game data received from server" << endl;
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
			cout << "Disconnected from server, aborting." << endl;
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
