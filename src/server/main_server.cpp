#include <iostream>

#include "../common/game.h"
#include "../common/map/world.h"
#include "net/server.h"

using namespace std;
using namespace sf;

Game game(false, "map.tmx");
Net::Server server(45612, 45612, &game);

int main_server() {


	return 0;
}
