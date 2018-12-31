//
// Created by Henrik Nielsen on 19/11/2018.
//
#include "System.h"

namespace Ecs::Systems {

    void System::Update() {
        int i = 0;
        std::for_each(world.Mask.begin(), world.Mask.end(), [&]( int mask) {
            if (HasRequiredComponents(mask))
                OnUpdate(i);
            i++;
        });
    }

    System::System(World &world) : world(world) { }

    bool System::HasRequiredComponents(int mask ) {
        return (mask & RequiredComponentsMask) == RequiredComponentsMask;
    }

}

