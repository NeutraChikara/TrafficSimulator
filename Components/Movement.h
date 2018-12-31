//
// Created by Henrik Nielsen on 03/12/2018.
//

#ifndef TRAFFICSIMULATOR_VELOCITY_H
#define TRAFFICSIMULATOR_VELOCITY_H


#include "Component.h"

namespace Ecs::Components {
    struct Movement : Component {
        Movement(unsigned int maxSpeed = 20, unsigned int speed = 0, unsigned int acceleration = 1,
                             unsigned int deceleration = 2);

        int Speed; // TODO: lav til doubles
        unsigned int MaxSpeed;
        unsigned int Acceleration;
        unsigned int Deceleration;
    };
}

#endif //TRAFFICSIMULATOR_VELOCITY_H
