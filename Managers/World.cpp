//
// Created by henrik on 27-11-2018.
//
#include "World.h"

namespace Ecs::Managers {
    void World::Addmask(Entity::Id id, int ComponentId) {
        mask[id] |= 1 << ComponentId;
    }

    uint32_t World::Getmask(Entity::Id id) {
        return mask[id];
    }

//TODO: Avoid using list of entities
    Entity World::CreateEntity() {
        for (int j = 0; j < mask.size(); ++j) {
            if (mask[j] == 0)
                return j;
        }
        if (mask.size() >= EntityCount - 1)
            return EntityCount - 1;
        mask.push_back(0);
        return mask.size() - 1;
    }

    void World::Kill(Entity e) {
        mask[e.GetId()] = 0;

    }
}

