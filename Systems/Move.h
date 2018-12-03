//
// Created by Henrik Nielsen on 03/12/2018.
//

#ifndef TRAFFICSIMULATOR_MOVE_H
#define TRAFFICSIMULATOR_MOVE_H


#include "System.h"

class Move : public System {
public:
    Move(World& world);
    void OnUpdate(Entity e) ;
};


#endif //TRAFFICSIMULATOR_MOVE_H
