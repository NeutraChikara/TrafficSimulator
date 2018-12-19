//
// Created by Henrik Nielsen on 19/11/2018.
//
#include "System.h"

namespace Ecs::Systems {

    void System::Update() {
        std::for_each(world.entities.begin(), world.entities.end(), [this](Entity e) {
            if (HasRequiredComponents(e))
                OnUpdate(e);
        });
    }

    System::System(World &world) : world(world) { }

    bool System::HasRequiredComponents(Entity entity) {
        return (world.Getmask(entity.GetId()) & RequiredComponentsMask) == RequiredComponentsMask;
    }

}

