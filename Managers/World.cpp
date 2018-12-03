//
// Created by henrik on 27-11-2018.
//
#include "World.h"

void World::Addmask(Entity::Id id,int ComponentId ){
    mask[id] |= 1<<ComponentId;
}

uint32_t World::Getmask(Entity::Id id) {
    return mask[id];
}

World::World() {

}
//TODO: Avoid using list of entities
Entity World::CreateEntity() {
    auto id = entities.size();
    entities.push_back(Entity(id));
    return entities[id];
}


