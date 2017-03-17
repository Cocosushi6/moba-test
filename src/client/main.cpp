#include <iostream>
#include "game.h"
#include "SFML/Network.hpp"

using namespace std;
using namespace sf;

Client client;
Game game;

int main() {
	client(IpAddress("127.0.0.1"), 1662, 1662);


	return 0;
}

