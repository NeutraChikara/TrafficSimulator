//
// Created by henrik on 27-11-2018.
//

#ifndef TRAFFICSIMULATOR_ENTITY_H
#define TRAFFICSIMULATOR_ENTITY_H


#include <cstdint>
#include "../Components/ComponentUtility.h"

class EntityManager;

class Entity {
public:
    using Id = uint8_t;

    Entity(Id id, EntityManager *entityManager);

    template<typename T, typename... Args>
    void AddComponent(Args &&... args);

    Id GetId();

private:
    Id id;
    EntityManager *entityManager;
};

template<typename T, typename... Args>
void Entity::AddComponent(Args &&... args) {
    // Perfect forwarding
    entityManager->AddComponent<T>(*this, std::forward<Args>(args)...);
    }

// EntityManager is here and not in seperate class due to cyclic dependency
class EntityManager {
public:
    EntityManager();

    Entity CreateEntity();

    template<typename T, typename... Args>
    void AddComponent(Entity e, Args &&... args);

    template <typename T>
    void AddComponent(Entity e, T component);

private:
    Entity::Id idCounter;
};

template<typename T, typename... Args>
void EntityManager::AddComponent(Entity e, Args &&... args) {
    T component(std::forward<Args>(args) ...);
    AddComponent<T>(e, component);
}

template<typename T>
void EntityManager::AddComponent(Entity e, T component) {
    const auto componentId = ComponentUtility<T>::GetId();
    const auto entityId = e.GetId();
    std::shared_ptr<Pool<T>> componentPool = accommodateComponent<T>(); // TODO: Make pool, see https://github.com/tapio/ecs for how

    //if (entityId >= componentPool->getSize()) {
    //    componentPool->resize(versions.size());
    //}

    //componentPool->set(entityId, component);
    //componentMasks[entityId].set(componentId);
}

#endif //TRAFFICSIMULATOR_ENTITY_H
