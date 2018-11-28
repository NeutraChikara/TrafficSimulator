//
// Created by henrik on 27-11-2018.
//

#ifndef TRAFFICSIMULATOR_WORLD_H
#define TRAFFICSIMULATOR_WORLD_H


#include "../Entities/Entity.h"
#include <memory>
#include <vector>

class World {
public:
    World();
    Entity CreateEntity();
    void DestroyEntity(Entity e);
private:
    std::unique_ptr<EntityManager> entityManager;
    std::vector<Entity> createdEntities;
    std::vector<Entity> destroyedEntities;
};


#endif //TRAFFICSIMULATOR_WORLD_H
