//
// Created by Henrik Nielsen on 03/12/2018.
//

#ifndef TRAFFICSIMULATOR_POSITION_H
#define TRAFFICSIMULATOR_POSITION_H


#include "Component.h"

struct Transform : Component {
    Transform(int x = 0, int y = 0, int orientation = 0);
    int Orientation;
    int X;
    int Y;
};


#endif //TRAFFICSIMULATOR_POSITION_H
