#ifndef SRC_COMMON_OBJECTS_OBJECT_H_
#define SRC_COMMON_OBJECTS_OBJECT_H_

#include <string>
#include <iostream>
#include <vector>


namespace Objects {
	class GameEntityManager;
	class Game;

	class Object {
		public:
			Object(float mapX, float mapY, float mapZ, int heightZ, std::string name, Game *game, bool remote);
			virtual void update(long tickrate) = 0; //pure virtual method, Object is an abstract class
			virtual ~Object();
			int getHeightZ() const;
			float getLife() const;
			float getMana() const;
			float getMapX() const;
			float getMapY() const;
			float getMapZ() const;
			std::string& getName() const;
			void setHeightZ(int heightZ);
			void setMapX(float mapX);
			void setMapY(float mapY);
			void setMapZ(float mapZ);
			void setName(std::string& name);

		protected:
			bool remote = false;
			float mapX, mapY, mapZ;
			int heightZ;
			std::string name; //name is important : paths to 3D models are build according to this name
			Game *game;
	};

}

sf::Packet& operator<<(sf::Packet& packet, Objects::Object &obj);
sf::Packet& operator>>(sf::Packet& packet, Objects::Object &obj);

#endif /* SRC_COMMON_OBJECTS_OBJECT_H_ */
