//
// Created by TobiasHK on 01-Dec-18.
//
#ifndef TRAFFICSIMULATOR_LOGGER_H
#define TRAFFICSIMULATOR_LOGGER_H

#include <iostream>
#include "System.h"
#include "../Components/NameComponent.h"
#include "../Entities/Entity.h"
#include "../Components/Position.h"

class Logger : public System {
public:
    Logger(World & world):System(world){
        this->SetRequiredComponents<Position>();
    }

    void OnUpdate(Entity e){
        std::cout << __FUNCTION__ << std::endl;
        std::cout << "x: " <<  world.GetComponent<Position>(e.GetId()).X << std::endl;
        std::cout << "y: " <<  world.GetComponent<Position>(e.GetId()).Y << std::endl;
    }

};


#endif
