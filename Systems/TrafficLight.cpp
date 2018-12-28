//
// Created by Henrik Nielsen on 15/12/2018.
//

#include "TrafficLight.h"
#include "../Components/TrafficLight.h"
namespace Ecs::Systems {
    TrafficLight::TrafficLight(World &world) : System(world) {
        SetRequiredComponents<Ecs::Components::TrafficLight>();
    }

    void TrafficLight::OnUpdate(Entity e) {
        auto &light = world.GetComponent<Ecs::Components::TrafficLight>(e.GetId());
        light.LastChangedCounter++;
        if (light.LastChangedCounter > light.CountsBeforeChange) {
            light.LastChangedCounter = 0;
            light.IsDirectionAllowed[0] = !light.IsDirectionAllowed[0];
            light.IsDirectionAllowed[1] = !light.IsDirectionAllowed[1];
            light.IsDirectionAllowed[2] = !light.IsDirectionAllowed[2];
            light.IsDirectionAllowed[3] = !light.IsDirectionAllowed[3];
        }
    }
}