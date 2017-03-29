#include <iostream>

#include "net/server.h"
#include "../common/game.h"

using namespace std;
using namespace sf;

Game game;
Server server;

int main() {
	server(45612, 45612, &game);



	return 0;
}
