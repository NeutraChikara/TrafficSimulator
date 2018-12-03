//
// Created by Henrik Nielsen on 03/12/2018.
//

#ifndef TRAFFICSIMULATOR_VELOCITY_H
#define TRAFFICSIMULATOR_VELOCITY_H


#include "Component.h"

struct Velocity : Component {
    Velocity(int dx = 0, int dy = 0);

    int Dx;
    int Dy;
};


#endif //TRAFFICSIMULATOR_VELOCITY_H
