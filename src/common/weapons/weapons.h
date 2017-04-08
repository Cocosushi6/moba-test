#ifndef SRC_WEAPON_H
#define SRC_WEAPON_H

#include <iostream>
#include <string>
#include <vector>

#include "../objects/object.h"
#include "../objects/entities/entity.h"

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

