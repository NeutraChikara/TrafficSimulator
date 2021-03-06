//
// Created by Henrik Nielsen on 21/12/2018.
//

#include "VehicleCollisionPrevention.h"
#include <boost/math/constants/constants.hpp>
#include <cmath>

Ecs::Systems::VehicleCollisionPrevention::VehicleCollisionPrevention(World &world) : System(world) {
    SetRequiredComponents<Transform, Movement>();
}

void Ecs::Systems::VehicleCollisionPrevention::OnUpdate(Entity e) {
    auto transform = world.GetComponent<Transform>(e.GetId());
    auto &velocity = world.GetComponent<Movement>(e.GetId());
    bool inTraffic = false;
    int i = 0;
    std::for_each(world.Mask.begin(), world.Mask.end(),
                  [&](int mask) {
                      if (HasRequiredComponents(mask) && i != e.GetId()) {
                          auto otherTransform = world.GetComponent<Transform>(i);
                          if (!inTraffic && SameDirection(transform, otherTransform) &&
                              DistanceBetween(transform, otherTransform) < 500 &&
                              LastVehicle(transform, otherTransform)) {
                              inTraffic = true;
                              velocity.Speed -= velocity.Deceleration;
                              if (velocity.Speed < 0) velocity.Speed = 0;
                              if(DistanceBetween(transform, otherTransform) < 5)
                              {
                                  world.Kill(e);
                                  world.Kill(i);
                              }
                          }
                      }
                      i++;
                  });

    if (!inTraffic) {
        velocity.Speed += velocity.Acceleration;
        if (velocity.Speed > velocity.MaxSpeed)velocity.Speed = velocity.MaxSpeed;

    }
}

int Ecs::Systems::VehicleCollisionPrevention::DistanceBetween(Transform transform, Transform otherTransform) {

    int vectorX = transform.X - otherTransform.X;
    int vectorY = transform.Y - otherTransform.Y;

    auto result = std::sqrt(vectorX * vectorX + vectorY * vectorY);
    return result;
}

bool Ecs::Systems::VehicleCollisionPrevention::SameDirection(Transform transform, Transform otherTransform) {
    auto result = std::abs(transform.Orientation - otherTransform.Orientation);
    return result < 100;
}

bool Ecs::Systems::VehicleCollisionPrevention::LastVehicle(Transform transform, Transform otherTransform) {
    auto angle = AngleBetweenTransforms(transform, otherTransform);
    auto fov = 40;
    auto withinFov = std::abs(angle) < fov;

    return withinFov;
}

double Ecs::Systems::VehicleCollisionPrevention::AngleBetweenTransforms(Transform current, Transform other) {
    auto pi = boost::math::constants::pi<double>();
    auto angleInRad = current.Orientation * pi / 180; // TODO: Use literal
    auto x1 = std::cos(angleInRad);
    auto y1 = std::sin(angleInRad);
    auto x2 = other.X - current.X;
    auto y2 = other.Y - current.Y;

    auto dotProduct = x1 * x2 + y1 * y2;
    auto determinant = y1 * x2 - x1 * y2;

    return std::atan2(determinant, dotProduct) * 180 / pi;
}
