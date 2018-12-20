//
// Created by Henrik Nielsen on 03/12/2018.
//

#include "Move.h"
#include "../Components/Transform.h"
#include "../Components/Velocity.h"
#include "../Components/TrafficLight.h"
#include <boost/math/constants/constants.hpp>
#include <cmath>

using namespace Ecs::Components;

namespace Ecs::Systems {
    Move::Move(World &world) : System(world) {
        SetRequiredComponents<Transform, Velocity, Path>();
    }

    void Move::OnUpdate(Entity e) {
        auto &transform = world.GetComponent<Transform>(e.GetId());
        auto vel = world.GetComponent<Velocity>(e.GetId());
        auto &path = world.GetComponent<Path>(e.GetId());

        auto point = path.Path[path.indexOfCurrentPoint];

        auto pointX = world.GetComponent<Transform>(point.trafficLightEntityId).X;
        auto pointY = world.GetComponent<Transform>(point.trafficLightEntityId).Y;

        int vectorX = pointX - transform.X;
        int vectorY = pointY - transform.Y;

        double length = std::sqrt(vectorX * vectorX + vectorY * vectorY);

        if ( length < 50 && !LightIsGo(point))
            return;

        if (length < 20) {
            path.indexOfCurrentPoint++;
            if (path.indexOfCurrentPoint == path.Path.size()) {
                world.kill(e);
                return;
            }
            point = path.Path[path.indexOfCurrentPoint];

            pointX = world.GetComponent<Transform>(point.trafficLightEntityId).X;
            pointY = world.GetComponent<Transform>(point.trafficLightEntityId).Y;

            vectorX = pointX - transform.X;
            vectorY = pointY - transform.Y;
        }

        length = std::sqrt(vectorX * vectorX + vectorY * vectorY);
        double speed = std::sqrt(vel.Dx * vel.Dx + vel.Dy * vel.Dy);
        transform.X += (vectorX / length) * speed;
        transform.Y += (vectorY / length) * speed;

        if(vectorX != 0)
            transform.Orientation = std::atan(vectorY/vectorX) * 180 / boost::math::constants::pi<double>();
    }

    bool Move::LightIsGo(Ecs::DataStructures::Node trafficLight) {
        auto light = world.GetComponent<TrafficLight>(trafficLight.trafficLightEntityId);
        return light.IsDirectionAllowed[trafficLight.entrancePoint];
    }
}
