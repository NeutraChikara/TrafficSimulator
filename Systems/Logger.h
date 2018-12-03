//
// Created by TobiasHK on 01-Dec-18.
//
#ifndef TRAFFICSIMULATOR_LOGGER_H
#define TRAFFICSIMULATOR_LOGGER_H

#include <iostream>
#include "System.h"
#include "../Components/NameComponent.h"
#include "../Entities/Entity.h"

class Logger : public System {
public:
    Logger(World & world):System(world){
        this->SetRequiredComponents<NameComponent>();
    }

    void OnUpdate(Entity e){
        std::cout << __FUNCTION__;
        std::cout << (int)e.GetId() << world.GetComponent<NameComponent>(e.GetId()).Name<< std::endl;

    }

};


#endif
