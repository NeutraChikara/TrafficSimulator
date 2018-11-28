//
// Created by henrik on 27-11-2018.
//

#include "Entity.h"

Entity::Entity(Entity::Id id, EntityManager* entityManager) : id(id), entityManager(entityManager) {
//    entityManager = std::make_unique<EntityManager>();
}

Entity::Id Entity::GetId() {
    return id;
}


EntityManager::EntityManager() : idCounter(0) {

}

Entity EntityManager::CreateEntity() {
    // TODO: Id's run free and are therefore not guaranteed not to clash at some point if you create more entities than causes idCounter to reset
    return Entity(idCounter++, this);
}
