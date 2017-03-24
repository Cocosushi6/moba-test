#include "packet.h"
#include "../../common/utils.h"

using namespace std;

GamePacket::PacketParser::PacketParser(Game *game) : game(game) {
        
}

int GamePacket::PacketParser::parsePacket(sf::Packet packet) {
    std::string descriptor;
    if(!packet >> descriptor) {
        cout << "No descriptor in packet, discarding" << endl;
        return -1;
    }
    
    if(descriptor == "INPUT") {
        InputState state;
        if(!packet >> state) {
            cout << "Wrong descriptor, no inputState in packet with descriptor " << descriptor << endl;
            return -1;
        }
    }
    
    return 0;
}

GamePacket::PacketParser::~PacketParser() {
    delete game;
}
