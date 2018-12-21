//
// Created by Henrik Nielsen on 21/12/2018.
//

#ifndef TRAFFICSIMULATOR_VEHICLECOLLISIONPREVENTION_H
#define TRAFFICSIMULATOR_VEHICLECOLLISIONPREVENTION_H

#include "System.h"

namespace Ecs::Systems {
    class VehicleCollisionPrevention : public System {
    public:
        VehicleCollisionPrevention(World &world);

    private:
        void OnUpdate(Entity e) override;

        int DistanceBetween(Transform transform, Transform otherTransform);

        bool SameDirection(Transform transform, Transform otherTransform);

        bool LastVehicle(Transform transform, Transform otherTransform);

        double Angle(int x, int y);
    };
}

#endif //TRAFFICSIMULATOR_VEHICLECOLLISIONPREVENTION_H
