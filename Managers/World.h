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
#include "../Components/RoadGraph.h"
#include <tuple>
#include <vector>
#include <stdexcept>

namespace Ecs::Managers {
    using namespace Ecs::Components;
    using namespace Ecs::Entities;

    typedef std::tuple<SpeedAndAcceleration, Transform, Ecs::Components::Path, TrafficLight, Ecs::Components::Render, RoadGraph> Components;

    class World {
    public:
        static const unsigned int EntityCount = 1000;

        Entity CreateEntity();

        template<typename T>
        void AddComponent(T component, Entity entity);

        template<typename T>
        T &GetComponent(Entity::Id id);

        uint32_t Getmask(Entity::Id id);

        void Kill(Entity e);

        std::vector<Entity> Entities;
        //uint32_t mask[EntityCount]{0};
        std::vector<uint32_t> mask;
    private:
        void Addmask(Entity::Id id, int ComponentId);

        Components components[EntityCount];

    };

    template<typename T>
    void World::AddComponent(T component, Entity entity) {
        std::get<T>(components[entity.GetId()]) = component;
        Addmask(entity.GetId(), Ecs::Components::ComponentUtility<T>::GetId());
    }

//TODO: Should return a copy and have set/update component method
    template<typename T>
    T &World::GetComponent(Entity::Id id) {
        if(id >= mask.size() || !(mask[id] & 1 << ComponentUtility<T>::GetId()) )
            throw  std::invalid_argument("No such component or entity exists");
        return std::get<T>(components[id]);
    }
}

#endif //TRAFFICSIMULATOR_WORLD_H
