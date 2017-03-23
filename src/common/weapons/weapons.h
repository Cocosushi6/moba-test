#ifndef SRC_WEAPON_H
#define SRC_WEAPON_H

#include <iostream>
#include <string>
#include <vector>

namespace Weapons {
    
    class Weapon {
        public:
            Weapon(Objects::Entities::Entity *carrier);
            void use();
        private:
            Objects::Entities::Entity *carrier;
    };
    
}

#endif /* SRC_WEAPON_H */
