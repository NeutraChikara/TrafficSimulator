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
        auto id = Entities.size();
        Entities.push_back(Entity(id));
        return Entities[id];
    }

    void World::Kill(Entity e) {
        mask[e.GetId()] = 0;

    }
}

