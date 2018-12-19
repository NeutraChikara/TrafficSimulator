//
// Created by TobiasHK on 01-Dec-18.
//
#ifndef TRAFFICSIMULATOR_LOGGER_H
#define TRAFFICSIMULATOR_LOGGER_H

#include "System.h"
#include "../Entities/Entity.h"

namespace Ecs::Systems {

    class Logger : public System {
    public:
        Logger(World &world);
        void OnUpdate(Entity e);
    };
}

#endif
