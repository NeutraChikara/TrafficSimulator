//
// Created by Henrik Nielsen on 21/12/2018.
//

#include "VehicleCollisionPrevention.h"
#include <boost/math/constants/constants.hpp>
#include <cmath>

Ecs::Systems::VehicleCollisionPrevention::VehicleCollisionPrevention(World &world) : System(world) {
    SetRequiredComponents<Transform, SpeedAndAcceleration>();
}

void Ecs::Systems::VehicleCollisionPrevention::OnUpdate(Entity e) {
    auto transform = world.GetComponent<Transform>(e.GetId());
    auto &velocity = world.GetComponent<SpeedAndAcceleration>(e.GetId());
    bool inTraffic = false;
    std::for_each(world.entities.begin(), world.entities.end(),
                  [&](Entity other) {
                      if (HasRequiredComponents(other) && other.GetId() != e.GetId()) {
                          auto otherTransform = world.GetComponent<Transform>(other.GetId());
                          if (!inTraffic && SameDirection(transform, otherTransform) &&
                              LastVehicle(transform, otherTransform) &&
                              DistanceBetween(transform, otherTransform) < 500) {
                              inTraffic = true;
                              velocity.Speed -= velocity.Deceleration;
                              if (velocity.Speed < 0) velocity.Speed = 0;
                              std::cout << e.GetId();
                          }
                      }
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
    return result < 40;
}

bool Ecs::Systems::VehicleCollisionPrevention::LastVehicle(Transform transform, Transform otherTransform) {
    int vectorX = transform.X - otherTransform.X;
    int vectorY = transform.Y - otherTransform.Y;

    double angle = Angle(vectorX, vectorY);

    auto deltaAngle = angle - transform.Orientation;

    int fov = 40;
    auto result = std::abs(deltaAngle) < fov;

    return result;
}

double Ecs::Systems::VehicleCollisionPrevention::Angle(int x, int y) {

    if (x == 0)
        return (y > 0 ? 90 : -90);

    int i = 0;

    if (y < 0)
        i = 180;
    return std::atan((double) y / x) * 180 / boost::math::constants::pi<double>() + i;
}


//void whatever()
//{
//    int deltaAngle = 0;
//    if (vectorX == 0) {
//        deltaAngle = (vectorY > 0 ? 90 : -90) - transform.Orientation;
//    }
//
//    if (vectorX != 0) {
//        if (vectorX < 0 && vectorY == 0)
//            deltaAngle = -180;
//        else {
//
//            auto transformDirection = transform.Orientation;
//            deltaAngle = angleBetweenCars - transformDirection;
//        }
//    }
//
//    if (vectorX < 0 && vectorY > 0)
//        deltaAngle -= 90;
//
//}