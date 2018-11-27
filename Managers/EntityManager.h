//
// Created by henrik on 27-11-2018.
//

#ifndef TRAFFICSIMULATOR_ENTITYMANAGER_H
#define TRAFFICSIMULATOR_ENTITYMANAGER_H


#include "../Entities/Entity.h"

class EntityManager {
public:
    EntityManager();
    Entity CreateEntity();
private:
    Entity::Id idCounter;
};


#endif //TRAFFICSIMULATOR_ENTITYMANAGER_H
