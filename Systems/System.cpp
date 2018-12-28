//
// Created by Henrik Nielsen on 19/11/2018.
//
#include "System.h"

namespace Ecs::Systems {

    void System::Update() {
        std::for_each(world.mask.begin(), world.mask.end(), [this]( int mask, int e) {
            if (HasRequiredComponents(e))
                OnUpdate(e);
        });
    }

    System::System(World &world) : world(world) { }

    bool System::HasRequiredComponents(int mask ) {
        return (mask & RequiredComponentsMask) == RequiredComponentsMask;
    }

}

