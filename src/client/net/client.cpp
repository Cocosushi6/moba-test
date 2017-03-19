#include <iostream>
#include <string>
#include <vector>

#include "client.h"
#include "packet.h"
#include "consts.h"

using namespace sf;
using namespace std;
using namespace Packet;

Client::Client(IpAddress address, int udpPort, int tcpPort, GamePacket::PacketParser *parser) : serverAddress(address), udpPort(udpPort), tcpPort(tcpPort), packetParser(parser) {

}

int Client::connect() {
	//connect TCP socket to server on port
	Socket::Status success = tcpSocket.connect(serverAddress, udpPort);
	if(success != Socket::Done) {
		std::cout << "Failed to connect tcp socket ! Aborting." << std::endl;
		return -1;
	}
	tcpSocket.setBlocking(false);

	if(udpSocket.bind(tcpPort) != Socket::Done) {
		std::cout << "Failed to bind udp socket ! Aborting. " << std::endl;
		return -1;
	}
	udpSocket.setBlocking(false);

	return 0;
}

void Client::poll() {
	IpAddress sender;
	unsigned short senderPort;
	if(udpSocket.receive(dataPacket, sender, senderPort) != (Socket::Done || Socket::NotReady)) {
		cout << "Error while receiving UDP packet" << endl;
	}
	packetParser->parse(dataPacket);

	if(tcpSocket.receive(dataPacket) != (Socket::Done || Socket::NotReady)) {
		cout << "Error while reading TCP packet" << endl;
	}
	packetParser->parse(dataPacket);
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
