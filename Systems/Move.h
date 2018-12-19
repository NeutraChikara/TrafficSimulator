//
// Created by Henrik Nielsen on 03/12/2018.
//

#ifndef TRAFFICSIMULATOR_MOVE_H
#define TRAFFICSIMULATOR_MOVE_H


#include "System.h"
namespace Ecs::Systems {
    class Move : public Ecs::Systems::System {
    public:
        Move(World &world);

        void OnUpdate(Entity e);

    private:
        bool LightIsGo(Ecs::DataStructures::Node trafficLight);
    };
}

#endif //TRAFFICSIMULATOR_MOVE_H
