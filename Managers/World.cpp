//
// Created by henrik on 27-11-2018.
//

#include "World.h"

World::World() {
    // Kunne have lavet dependency injection i stedet, men kræver et interface samt ekstra håndtering af levetiden
    entityManager = std::make_unique<EntityManager>();
}


Entity World::CreateEntity() {
    auto e = entityManager->CreateEntity();
    createdEntities.push_back(e);
    return e;
}

void World::DestroyEntity(Entity e) {
    destroyedEntities.push_back(e);
}



