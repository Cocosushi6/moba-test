#include "utils.h"


sf::Packet& operator <<(sf::Packet& packet, const InputState& state) {
	return packet << state.state << state.key << state.timestamp;
}

sf::Packet& operator >>(sf::Packet& packet, InputState& state) {
	return packet >> state.state >> state.key >> state.timestamp;
}
