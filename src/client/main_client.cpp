#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <thread>

#include "net/packet.h"
#include "net/client.h"
#include "rendering/renderer.h"
#include "rendering/utils/utils.h"
#include "../common/map/world.h"
#include "../common/game.h"
#include "utils/utils.h"
#include "main_client.h"

using namespace std;

//Init methods

int main_client(std::string serverAddress, int port) {
	cout << "running main_client ! " << endl;
	static Game game = Game();
	static bool initDone = false;
	static bool running = true;
	
	static Objects::Entities::Player *attachedPlayer;

	static GamePacket::PacketParser parser(&game);
	static Client client(sf::IpAddress(serverAddress), 45612, &parser);

	static sf::Window window;

	//init game objects
	cout << "Launching Game !" << endl;

	sf::ContextSettings settings;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.depthBits = 24;

	window.create(sf::VideoMode(1024, 720), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setVerticalSyncEnabled(true);
	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);
	window.setActive(true);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {
		std::cout << "Couldn't initialize GLEW" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_EQUAL);

	cout << "window initialised, OpenGL context version : " << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << endl;

	//connect to server
	cout << "Connecting to client, please wait..." << endl;

	bool connected = client.connect();
	if(!connected) {
		cout << "Failed to connect to client ! Please check the IP address you entered and if the server is running " << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(2500)); //Leave time for reading
		return -1; //Exit.
	}

	static Rendering::Renderer renderer(&window, &game);
	InputManager inputManager(&game, &client, &renderer);

	sf::Clock deltaTimer;
	initDone = true;

	while(running && client.isConnected()) {
		sf::Time delta = deltaTimer.getElapsedTime();
		deltaTimer.restart();
		//Event loop
		sf::Event ev;
		while(window.pollEvent(ev)) {
			switch(ev.type) {
				case sf::Event::Closed :
					running = false;
					break;
			}
		}
		client.poll();
		inputManager.processInput(delta);
		renderer.getCamera()->processMouse(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		renderer.render();
	}
	cout << "Ended client game, OGL version : " << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << endl;
	window.setActive(false);
	return 0;
}

