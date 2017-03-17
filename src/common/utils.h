#ifndef SRC_UTILS_H
#define SRC_UTILS_H

#include <string>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

class InputState {
	public:
		bool state;
		std::string key;
		sf::Uint64 timestamp;
};

#endif
