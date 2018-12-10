//
// Created by TobiasHK on 01-Dec-18.
//
#ifndef TRAFFICSIMULATOR_LOGGER_H
#define TRAFFICSIMULATOR_LOGGER_H

#include <iostream>
#include "System.h"
#include "../Components/NameComponent.h"
#include "../Entities/Entity.h"
#include "../Components/Transform.h"

class Logger : public System {
public:
    Logger(World & world):System(world){
        this->SetRequiredComponents<Transform>();
    }

    void OnUpdate(Entity e){
        std::cout << "Id: " << e.GetId() << " " << "x: " <<  world.GetComponent<Transform>(e.GetId()).X << std::endl;
        std::cout << "Id: " << e.GetId() << " " << "y: " <<  world.GetComponent<Transform>(e.GetId()).Y << std::endl;
    }

};


#endif
