//
// Created by henrik on 27-11-2018.
//
#include "World.h"

namespace Ecs::Managers {
    void World::Addmask(Entity::Id id, int componentId) {
        Mask[id] |= 1 << componentId;
    }

//TODO: Avoid using list of entities
    Entity World::CreateEntity() {
        for (int j = 0; j < Mask.size(); ++j) {
            if (Mask[j] == 0)
                return j;
        }
        if (Mask.size() >= EntityCount - 1)
            return EntityCount - 1;
        Mask.push_back(0);
        return Mask.size() - 1;
    }

    void World::Kill(Entity e) {
        Mask[e.GetId()] = 0;

    }
}

