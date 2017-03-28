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
bool initDone = false;

Rendering::Renderer renderer;
sf::Window window;

int main() {
	
	initWindow();
	
	parser(&game);
	client(sf::IpAddress("127.0.0.1"), 1662, 1662, &parser);
	
	renderer(&window, &map, &game); //Constructor TODO
	
	//game loop
	while(window.isOpen()) {
		
		//event loop
		sf::Event ev;
		while(window.pollEvent(ev)) {
			
		}
		
		
		//now, render.
	}

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
