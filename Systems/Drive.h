//
// Created by Henrik Nielsen on 03/12/2018.
//

#ifndef TRAFFICSIMULATOR_MOVE_H
#define TRAFFICSIMULATOR_MOVE_H


#include "System.h"
namespace Ecs::Systems {
    class Drive : public Ecs::Systems::System {
    public:
        Drive(World &world);

        void OnUpdate(Entity e);

    private:
        bool LightIsGo(Ecs::DataStructures::Node trafficLight);

        int GetXCompensation(int entrypoint, int exitPoint);

        int GetYCompensation(int entrypoint, int exitPoint);

        int GetEntrypoint(int x, int y, Transform &transform);

        int GetExitPoint(int x, int y, Path &path);

        int CalculateOrientation(int vectorX, int vectorY);
    };
}

#endif //TRAFFICSIMULATOR_MOVE_H
