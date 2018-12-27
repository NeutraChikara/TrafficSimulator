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

        auto point = path.Nodes[path.IndexOfCurrentNode];
        auto pointX = world.GetComponent<Transform>(point.trafficLightEntityId).X;
        auto pointY = world.GetComponent<Transform>(point.trafficLightEntityId).Y;

        pointX += GetXCompensation(point.entrancePoint, point.exitPoint);
        pointY += GetYCompensation(point.entrancePoint, point.exitPoint);

        int vectorX = pointX - transform.X;
        int vectorY = pointY - transform.Y;

        double length = std::sqrt(vectorX * vectorX + vectorY * vectorY);

        if (length < 700 && length > 500  && !LightIsGo(point)) // TODO: Reeable to stop for red traffic light
            return;

        if (length < 20) {
            path.IndexOfCurrentNode++;
            if (path.IndexOfCurrentNode == path.Nodes.size()) {
                world.Kill(e);
                return;
            }
            point = path.Nodes[path.IndexOfCurrentNode];

            pointX = world.GetComponent<Transform>(point.trafficLightEntityId).X;
            pointY = world.GetComponent<Transform>(point.trafficLightEntityId).Y;

            vectorX = pointX - transform.X;
            vectorY = pointY - transform.Y;
        }

        length = std::sqrt(vectorX * vectorX + vectorY * vectorY);
        transform.X += (vectorX / length) * vel.Speed;
        transform.Y += (vectorY / length) * vel.Speed;


        auto x1 = vectorX;
        auto y1 = vectorY;
        auto x2 = 1;
        auto y2 = 0;

        auto dotProduct = x1 * x2 + y1 * y2;
        auto determinant = y1 * x2 - x1 * y2;
        auto angle = atan2(determinant, dotProduct) * 180 / boost::math::constants::pi<double>();

        transform.Orientation = static_cast<int>(angle);
    }

    bool Drive::LightIsGo(Ecs::DataStructures::Node trafficLight) {
        auto light = world.GetComponent<TrafficLight>(trafficLight.trafficLightEntityId);
        return light.IsDirectionAllowed[trafficLight.entrancePoint];
    }

    int Drive::GetXCompensation(int entrypoint, int exitPoint) {
        if (entrypoint == 1 || entrypoint == 3) {
            return (entrypoint == 1 ? -200 : 200);
        } else if (exitPoint == 1 || exitPoint == 3) {
            return (exitPoint != 1 ? -200 : 200);
        } else
            return 0;
    }

    int Drive::GetYCompensation(int entrypoint, int exitPoint) {
        if (entrypoint == 0 || entrypoint == 2) {
            return (entrypoint == 0 ? -200 : 200);
        } else if (exitPoint == 0 || exitPoint == 2) {
            return (exitPoint != 0 ? -200 : 200);
        } else
            return 0;
    }
}

