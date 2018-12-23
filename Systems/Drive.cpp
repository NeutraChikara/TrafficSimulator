//
// Created by Henrik Nielsen on 03/12/2018.
//

#include "Drive.h"
#include "../Components/Transform.h"
#include "../Components/SpeedAndAcceleration.h"
#include "../Components/TrafficLight.h"
#include <boost/math/constants/constants.hpp>
#include <cmath>

using namespace Ecs::Components;

namespace Ecs::Systems {
    Drive::Drive(World &world) : System(world) {
        SetRequiredComponents<Transform, SpeedAndAcceleration, Path>();
    }

    void Drive::OnUpdate(Entity e) {
        auto &transform = world.GetComponent<Transform>(e.GetId());
        auto vel = world.GetComponent<SpeedAndAcceleration>(e.GetId());
        auto &path = world.GetComponent<Path>(e.GetId());

        auto point = path.Nodes[path.IndexOfCurrentPoint];

        auto pointX = world.GetComponent<Transform>(point.trafficLightEntityId).X;
        auto pointY = world.GetComponent<Transform>(point.trafficLightEntityId).Y;

        int vectorX = pointX - transform.X;
        int vectorY = pointY - transform.Y;

        double length = std::sqrt(vectorX * vectorX + vectorY * vectorY);

        //if (length < 50 && !LightIsGo(point))
          //  return;

        if (length < 20) {
            path.IndexOfCurrentPoint++;
            if (path.IndexOfCurrentPoint == path.Nodes.size()) {
                world.kill(e);
                return;
            }
            point = path.Nodes[path.IndexOfCurrentPoint];

            pointX = world.GetComponent<Transform>(point.trafficLightEntityId).X;
            pointY = world.GetComponent<Transform>(point.trafficLightEntityId).Y;

            vectorX = pointX - transform.X;
            vectorY = pointY - transform.Y;
        }

        length = std::sqrt(vectorX * vectorX + vectorY * vectorY);
        transform.X += (vectorX / length) * vel.Speed;
        transform.Y += (vectorY / length) * vel.Speed;

        if (vectorX != 0)
        {
            auto result = std::atan((double)vectorY / vectorX) * 180 / boost::math::constants::pi<double>();
            transform.Orientation = result;
        }
        else if(vectorY < 0)
        {
            transform.Orientation = -90;
        }
        else {
            transform.Orientation = 90;
        }
    }

    bool Drive::LightIsGo(Ecs::DataStructures::Node trafficLight) {
        auto light = world.GetComponent<TrafficLight>(trafficLight.trafficLightEntityId);
        return light.IsDirectionAllowed[trafficLight.entrancePoint];
    }
}
