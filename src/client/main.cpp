#include <iostream>
#include "game.h"
#include "SFML/Network.hpp"
#include "net/packet.h"

using namespace std;

void initGL();


Client client;
Game game;
GamePacket::PacketParser parser;

bool initDone = false;
static int SCREEN_WIDTH = 640;
static int SCREEN_HEIGHT = 480;

int main() {
	client(sf::IpAddress("127.0.0.1"), 1662, 1662, &parser);



	return 0;
}

void initGL() {

}
