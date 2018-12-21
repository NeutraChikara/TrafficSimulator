//
// Created by Henrik Nielsen on 19/12/2018.
//

#include "Logger.h"
#include <iostream>
#include "../Components/Transform.h"

namespace Ecs::Systems {
    Logger::Logger(World &world) : System(world) {
        SetRequiredComponents<Transform>();
    }

    void Logger::OnUpdate(Entity e) {
        std::cout << "Id: " << e.GetId() << " " << "x: " << world.GetComponent<Transform>(e.GetId()).X <<" " << "y: " << world.GetComponent<Transform>(e.GetId()).Y << std::endl;
    }
}