#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <TGUI/TGUI.hpp>

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

int main_client() {
	cout << "running main_client ! " << endl;
	static Game game = Game();
	static bool initDone = false;

	static GamePacket::PacketParser parser(&game);
	static Client client(sf::IpAddress("127.0.0.1"), 45612, 45612, &parser);

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



	while(window.isOpen()) {
		//Event loop
		sf::Event ev;
		while(window.pollEvent(ev)) {
			if(ev.type == sf::Event::Closed) {
				window.close();
			}
		}

	}
	cout << "Ended client game" << endl;
	return 0;
}

