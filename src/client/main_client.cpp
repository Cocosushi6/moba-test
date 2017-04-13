#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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

int main_client(std::string serverAddress) {
	cout << "running main_client ! " << endl;
	static Game game = Game();
	static bool initDone = false;

	static GamePacket::PacketParser parser(&game);
	static Client client(sf::IpAddress(serverAddress), 45612, 45612, &parser);

	static sf::RenderWindow window;
	static Rendering::Renderer renderer(&window, &game);

	static tgui::Gui gui(window);

	//init game objects
	cout << "Launching Game !" << endl;

	window.create(sf::VideoMode(1024, 720), "OpenGL", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	cout << "window initialised, OpenGL context version : " << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << endl;
	//game loop

	if(window.isOpen()) {
		renderer.drawLoadingScreen("Connecting to client, please wait ...");
	}

	bool connected = client.connect();
	if(!connected) {
		renderer.drawLoadingScreen("Failed to connect to client ! Please check the IP address you entered and if the server is running");
		std::this_thread::sleep_for(std::chrono::milliseconds(2500)); //Leave time for reading
		return -1; //Exit.
	}

	while(window.isOpen()) {
		//Event loop
		sf::Event ev;
		while(window.pollEvent(ev)) {
			if(ev.type == sf::Event::Closed) {
				window.close();
			}
		}

		renderer.render();
	}
	cout << "Ended client game" << endl;
	return 0;
}

