//
// Created by Henrik Nielsen on 15/12/2018.
//

#include "TrafficLightControl.h"
#include "../Components/TrafficLight.h"
namespace Ecs::Systems {
    TrafficLightControl::TrafficLightControl(World &world) : System(world) {
        SetRequiredComponents<TrafficLight>();
    }

    void TrafficLightControl::OnUpdate(Entity e) {
        auto &light = world.GetComponent<TrafficLight>(e.GetId());
        light.LastChangedCounter++;
        if (light.LastChangedCounter > 50) {
            light.LastChangedCounter = 0;
            light.IsDirectionAllowed[0] = !light.IsDirectionAllowed[0];
            light.IsDirectionAllowed[1] = !light.IsDirectionAllowed[1];
            light.IsDirectionAllowed[2] = !light.IsDirectionAllowed[2];
            light.IsDirectionAllowed[3] = !light.IsDirectionAllowed[3];
        }
    }
}