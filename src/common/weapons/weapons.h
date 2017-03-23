#ifndef SRC_WEAPON_H
#define SRC_WEAPON_H

#include <iostream>
#include <string>
#include <vector>

namespace Weapons {
    
    class Weapon {
        public:
            Weapon(Entity *carrier);
            void use();
        private:
            Entity *carrier;
    }
    
}

#endif /* SRC_WEAPON_H */