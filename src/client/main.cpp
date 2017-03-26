#include <iostream>
#include "SFML/Network.hpp"
#include "../common/game.h"
#include "SFML/OpenGL.hpp"
#include "SFML/Window.hpp"
#include "net/packet.h"
#include "rendering/renderer.h"
#include "../common/map/world.h"

using namespace std;

//Init methods
void drawMenu();
void initWindow();


//init game objects
Client client;
GamePacket::PacketParser parser;

Game game;
World::GameMap map;
bool initDone = false;

Rendering::Renderer renderer;
sf::Window window;

int main() {
	initWindow();
	parser(&game, &map);
	client(sf::IpAddress("127.0.0.1"), 1662, 1662, &parser);

	game(true, &map); //Constructor TODO

	renderer(&window, &map, &game); //Constructor TODO


	return 0;
}

void drawMenu() {

}

void initWindow() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 0;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	window.create(sf::VideoMode(1024, 720), "OpenGL", sf::Style::Default, settings);

}
