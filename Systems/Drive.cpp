//
// Created by Henrik Nielsen on 03/12/2018.
//

#include "Drive.h"
#include "../Components/Transform.h"
#include "../Components/Movement.h"
#include "../Components/TrafficLight.h"
#include <boost/math/constants/constants.hpp>
#include <cmath>

using namespace Ecs::Components;

namespace Ecs::Systems {
    Drive::Drive(World &world) : System(world) {
        SetRequiredComponents<Transform, Movement, Path>();
    }

    void Drive::OnUpdate(Entity e) {
        auto &transform = world.GetComponent<Transform>(e.GetId());
        auto &vel = world.GetComponent<Movement>(e.GetId());
        auto &path = world.GetComponent<Path>(e.GetId());

        auto node = path.Nodes[path.IndexOfCurrentNode];
        auto nodeX = world.GetComponent<Transform>(node.trafficLightEntityId).X;
        auto nodeY = world.GetComponent<Transform>(node.trafficLightEntityId).Y;

        nodeX += GetXCompensation(node.entrancePoint, node.exitPoint);
        nodeY += GetYCompensation(node.entrancePoint, node.exitPoint);

        auto vectorX = nodeX - transform.X;
        auto vectorY = nodeY - transform.Y;

        auto length = std::sqrt(vectorX * vectorX + vectorY * vectorY);

        if (length < 1000 && length > 500  && !LightIsGo(node))
        {
            vel.Speed -= vel.Deceleration;
            if (vel.Speed < 0) vel.Speed = 0;
        }

        if (length < 50) {
            path.IndexOfCurrentNode++;
            if (path.IndexOfCurrentNode == path.Nodes.size()) {
                world.Kill(e);
                return;
            }
            node = path.Nodes[path.IndexOfCurrentNode];

            nodeX = world.GetComponent<Transform>(node.trafficLightEntityId).X;
            nodeY = world.GetComponent<Transform>(node.trafficLightEntityId).Y;

            vectorX = nodeX - transform.X;
            vectorY = nodeY - transform.Y;
        }

        length = std::sqrt(vectorX * vectorX + vectorY * vectorY);
        transform.X += static_cast<int>((vectorX / length) * vel.Speed);
        transform.Y += static_cast<int>((vectorY / length) * vel.Speed);

        transform.Orientation = CalculateOrientation(vectorX, vectorY);
    }

    int Drive::CalculateOrientation(int vectorX, int vectorY)
    {
        auto x1 = vectorX;
        auto y1 = vectorY;
        auto x2 = 1;
        auto y2 = 0;

        auto dotProduct = x1 * x2 + y1 * y2;
        auto determinant = y1 * x2 - x1 * y2;
        auto angle = atan2(determinant, dotProduct) * 180 / boost::math::constants::pi<double>();
        return static_cast<int>(angle);
    }

    bool Drive::LightIsGo(Ecs::DataStructures::Node trafficLight) {
        auto light = world.GetComponent<TrafficLight>(trafficLight.trafficLightEntityId);
        return light.IsDirectionAllowed[trafficLight.entrancePoint];
    }

    int Drive::GetXCompensation(int entrypoint, int exitPoint) {
        if (entrypoint == 1 || entrypoint == 3) {
            return (entrypoint == 1 ? 200 : -200);
        } else if (exitPoint == 1 || exitPoint == 3) {
            return (exitPoint != 1 ? 200 : -200);
        } else
            return 0;
    }

    int Drive::GetYCompensation(int entrypoint, int exitPoint) {
        if (entrypoint == 0 || entrypoint == 2) {
            return (entrypoint == 0 ? 200 : -200);
        } else if (exitPoint == 0 || exitPoint == 2) {
            return (exitPoint != 0 ? 200 : -200);
        } else
            return 0;
    }
}

