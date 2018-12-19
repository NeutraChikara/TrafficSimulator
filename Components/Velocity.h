//
// Created by Henrik Nielsen on 03/12/2018.
//

#ifndef TRAFFICSIMULATOR_VELOCITY_H
#define TRAFFICSIMULATOR_VELOCITY_H


#include "Component.h"

namespace Ecs::Components {
    struct Velocity : Component {
        Velocity(int dx = 0, int dy = 0);

        int Dx; // TODO: lav til doubles
        int Dy;
    };
}

#endif //TRAFFICSIMULATOR_VELOCITY_H
