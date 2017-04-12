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
#include "../common/map/world.h"
#include "../common/game.h"
#include "utils/utils.h"
#include "main_client.h"

using namespace std;

//Init methods
static Game game = Game();
static bool initDone = false;

static GamePacket::PacketParser parser(&game);
static Client client(sf::IpAddress("127.0.0.1"), 45612, 45612, &parser);

static sf::RenderWindow window;
static Rendering::Renderer renderer(&window, &game);

static tgui::Gui gui(window);

int main_client(int argv, char** argc) {

	//init game objects
	cout << "Launching Game !" << endl;

	window.create(sf::VideoMode(1024, 720), "OpenGL", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);

	cout << "window initialised, OpenGL context version : " << window.getSettings().majorVersion << "." << window.getSettings().minorVersion << endl;
	//game loop

	while(window.isOpen()) {

	}

	return 0;
}

void connectCallback(sf::IpAddress ipAddress) {
	client.setServerAddress(ipAddress);
	client.connect();
}

void drawMenu() {
	tgui::TextBox::Ptr ipAddress = tgui::TextBox::create();
	tgui::Button::Ptr connectButton = tgui::Button::create("Connect to server");

	ipAddress->setSize(300, 40);
	ipAddress->setPosition(window.getSize().x / 2 - ipAddress->getSize().x / 2, window.getSize().y / 2 - ipAddress->getSize().y / 2);
	connectButton->setPosition(window.getSize().x / 2, window.getSize().y / 2 + 30);

	gui.add(ipAddress, "ipAddress");
	gui.add(connectButton, "connectButton");

	sf::IpAddress address(ipAddress->getText());
	connectButton->connect("pressed", connectCallback, address);
}
