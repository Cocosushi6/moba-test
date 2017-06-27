#include "utils.h"
#include <iostream>
#include <cmath>

using namespace std;

sf::Packet& operator <<(sf::Packet& packet, const InputState& state) {
	return packet << state.state << state.keyState << state.timestamp;
}

sf::Packet& operator >>(sf::Packet& packet, InputState& state) {
	return packet >> state.state >> state.keyState >> state.timestamp;
}

sf::Packet& operator<<(sf::Packet& packet, const sf::Vector2<int>& vec2) {
	return packet << vec2.x << vec2.y;
}

sf::Packet& operator>>(sf::Packet& packet,  sf::Vector2<int>& vec2) {
	packet >> vec2.x >> vec2.y;
	if(!packet) {
		cout << "Packet error : sf::Vector2 deserialization" << endl;
	}
	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, const sf::Vector2<double>& vec2) {
	return packet << vec2.x << vec2.y;
}

sf::Packet& operator>>(sf::Packet& packet,  sf::Vector2<double>& vec2) {
	packet >> vec2.x >> vec2.y;
	if(!packet) {
		cout << "Packet error : sf::Vector2 deserialization" << endl;
	}
	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, const sf::Vector3<double>& vec3) {
	return packet << vec3.x << vec3.y << vec3.z;
}

sf::Packet& operator>>(sf::Packet& packet, sf::Vector3<double>& vec3) {
	packet >> vec3.x >> vec3.y >> vec3.z;
	if(!packet) {
		cout << "Packet error : sf::Vector3 deserialization" << endl;
	}
	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, const Vertex& vertex) {
	return packet << vertex.coordinates << vertex.textCoords << vertex.normals;
}

sf::Packet& operator>>(sf::Packet& packet, Vertex& vertex) {
	packet >> vertex.coordinates >> vertex.textCoords >> vertex.normals;
	if(!packet) {
		cout << "Packet error : Vertex deserialization" << endl;
	}
	return packet;
}

sf::Packet& operator<<(sf::Packet& packet, const Quad& quad) {
	for(int i = 0; i < 4; i++) {
		packet << quad.vertices[i];
	}
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Quad& quad) {
	for(int i = 0; i < 4; i++) {
		packet >> quad.vertices[i];
	}
	if(!packet) {
		cout << "Packet error : Quad deserialization" << endl;
	}
	return packet;
}

vector<string> split(string s, char delim) {
	vector<string> elements;
	std::stringstream ss(s);
	string temp;
	while(std::getline(ss, temp, delim)) {
		if(!temp.empty()) {
			elements.push_back(temp);
		}
	}
	return elements;
}

void printQuad(Quad quad) {
	for(int i = 0; i < 4; i++) {
		cout << "Vertex " << i+1 << " : " << quad.vertices[i].coordinates.x << ", " << quad.vertices[i].coordinates.y << ", " << quad.vertices[i].coordinates.z << ";";
	}
}

float toRadians(float degrees) {
	return degrees * M_PI / 180;
}
