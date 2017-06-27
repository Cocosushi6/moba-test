#ifndef SRC_UTILS_H
#define SRC_UTILS_H

#include <string>
#include <sstream>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct InputState {
	bool state;
	std::string keyState;
	sf::Uint64 timestamp;
};

struct Vertex {
	sf::Vector3<double> coordinates;
	sf::Vector3<double> normals;
	sf::Vector2<double> textCoords;
};

//A square with 4 vertices (using EBOs)
struct Quad {
	Vertex vertices[4];
};

float toRadians(float degrees);
sf::Packet& operator<<(sf::Packet& packet, const InputState& state);
sf::Packet& operator>>(sf::Packet& packet, InputState& state);
sf::Packet& operator<<(sf::Packet& packet, const sf::Vector2<int>& vec2);
sf::Packet& operator>>(sf::Packet& packet, sf::Vector2<int>& vec2);
sf::Packet& operator<<(sf::Packet& packet, const sf::Vector2<int>& vec2);
sf::Packet& operator>>(sf::Packet& packet, sf::Vector2<double>& vec2);
sf::Packet& operator<<(sf::Packet& packet, const sf::Vector3<double>& vec3);
sf::Packet& operator>>(sf::Packet& packet, sf::Vector3<double>& vec3);
sf::Packet& operator<<(sf::Packet& packet, const Vertex& vertex);
sf::Packet& operator>>(sf::Packet& packet, Vertex& vertex);
sf::Packet& operator<<(sf::Packet& packet, const Quad& quad);
sf::Packet& operator>>(sf::Packet& packet, Quad& quad);
std::vector<std::string> split(std::string s, char delim);
void printQuad(Quad quad);


#endif
