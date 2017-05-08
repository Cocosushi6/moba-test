#include <iostream>

#include "../common/game.h"
#include "../common/map/world.h"
#include "net/server.h"

using namespace std;
using namespace sf;

int main_server(int argv, char** argc) {
	cout << "running server" << endl;
	Game game(false, "map.tmx");
	Net::Server server(45612, 45612, &game);
	server.poll();

	cout << "exiting server..." << endl;
	return 0;
}
