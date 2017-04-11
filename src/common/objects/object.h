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
			Object(float mapX, float mapY, int heightZ, std::string name, Game *game, bool remote);
			virtual void update(long tickrate) = 0; //pure virtual method, Object is an abstract class
			virtual ~Object();
			float getBasicDamage() const;
			float getDefense() const;
			int getHeightZ() const;
			float getLife() const;
			float getMana() const;
			float getMapX() const;
			float getMapY() const;
			const std::string& getName() const;
		protected:
			bool remote = false;
			float mapX, mapY;
			int heightZ;
			std::string name; //name is important : paths to 3D models are build according to this name
			float life = 10, defense = 10, mana = 0, basicDamage = 1;
			Game *game;
	};

}


#endif /* SRC_COMMON_OBJECTS_OBJECT_H_ */
