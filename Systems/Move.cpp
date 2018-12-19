//
// Created by Henrik Nielsen on 03/12/2018.
//

#include "Move.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/TrafficLight.h"
#include <cmath>

using namespace Ecs::Components;

namespace Ecs::Systems {
    Move::Move(World &world) : System(world) {
        SetRequiredComponents<Transform, Velocity, Path>();
    }

    void Move::OnUpdate(Entity e) {
        auto &pos = world.GetComponent<Transform>(e.GetId());
        auto vel = world.GetComponent<Velocity>(e.GetId());
        auto &path = world.GetComponent<Path>(e.GetId());

        auto node = path.Path[path.indexOfCurrentPoint];

        int x = node.X - pos.X;
        int y = node.Y - pos.Y;

        if (x < 50 && y < 50 && !LightIsGo(node)) return;

        if (x < 5 && y < 5) {
            path.indexOfCurrentPoint++;
            if (path.indexOfCurrentPoint >= path.Path.size()) {
                world.kill(e);
            }
            auto point = path.Path[path.indexOfCurrentPoint];
            x = point.X - pos.X;
            y = point.Y - pos.Y;
        }

        double length = std::sqrt(x * x + y * y);
        double speed = std::sqrt(vel.Dx * vel.Dx + vel.Dy * vel.Dy);
        pos.X += (x / length) * speed;
        pos.Y += (y / length) * speed;
    }

    bool Move::LightIsGo(Ecs::DataStructures::Node trafficLight) {
        auto light = world.GetComponent<TrafficLight>(trafficLight.trafficLightEntityId);
        return light.IsDirectionAllowed[trafficLight.entrancePoint];
    }
}
