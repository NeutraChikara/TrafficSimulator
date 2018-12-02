//
// Created by TobiasHK on 01-Dec-18.
//
#include <iostream>
#include "System.h"
#include "../Components/TestComponent1.h"
#include "../Entities/Entity.h"

#ifndef TRAFFICSIMULATOR_LOGGER_H
#define TRAFFICSIMULATOR_LOGGER_H


class Logger : public System {
public:
    Logger(World & world):System(world){
        this->SetRequiredComponents<TestComponent1>();
    }

    void OnUpdate(Entity e){
        std::cout << "OnUpdate()" << std::endl;
        std::cout << (int)e.GetId() << std::endl;
    }

};


#endif //TRAFFICSIMULATOR_LOGGER_H
