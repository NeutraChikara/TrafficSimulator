//
// Created by henrik on 27-11-2018.
//

#include "EntityManager.h"


EntityManager::EntityManager() : idCounter(0) {

}

Entity EntityManager::CreateEntity() {
    // TODO: Id's run free and are therefore not guaranteed not to clash at some point if you create more entities than causes idCounter to reset
    return Entity(idCounter++);
}
