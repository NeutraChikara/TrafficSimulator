//
// Created by henrik on 27-11-2018.
//

#ifndef TRAFFICSIMULATOR_WORLD_H
#define TRAFFICSIMULATOR_WORLD_H

#include "../Entities/Entity.h"
#include "../Components/ComponentUtility.h"
#include "../Components/SpeedAndAcceleration.h"
#include "../Components/Transform.h"
#include "../Components/Path.h"
#include "../Components/TrafficLight.h"
#include "../Components/Render.h"
#include <tuple>
#include <vector>

using namespace Ecs::Components;
using namespace Ecs::Entities;

namespace Ecs::Managers {
    typedef std::tuple<SpeedAndAcceleration, Transform, Ecs::Components::Path, TrafficLight, Ecs::Components::Render> Components;

    class World {
    public:
        static const uint8_t EntityCount = 100;

        Entity CreateEntity();

        template<typename T>
        void AddComponent(T component, Entity entity);

        template<typename T>
        T &GetComponent(Entity::Id id);

        uint32_t Getmask(Entity::Id id);

        std::vector<Entity> entities;

        void kill(Entity e);

    private:
        void Addmask(Entity::Id id, int ComponentId);

        Components components[EntityCount];
        uint32_t mask[EntityCount]{0};
    };

    template<typename T>
    void World::AddComponent(T component, Entity entity) {
        std::get<T>(components[entity.GetId()]) = component;
        Addmask(entity.GetId(), Ecs::Components::ComponentUtility<T>::GetId());
    }

//TODO: Should return a copy and have set/update component method
    template<typename T>
    T &World::GetComponent(Entity::Id id) {
        return std::get<T>(components[id]);
    }
}

#endif //TRAFFICSIMULATOR_WORLD_H
