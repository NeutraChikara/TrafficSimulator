//
// Created by Henrik Nielsen on 15/12/2018.
//

#ifndef TRAFFICSIMULATOR_TRAFFICLIGHTCONTROL_H
#define TRAFFICSIMULATOR_TRAFFICLIGHTCONTROL_H


#include "System.h"
namespace Ecs::Systems {
    class TrafficLight : public Ecs::Systems::System {
    public:
        TrafficLight(World &world);

    protected:
        void OnUpdate(Entity e) override;

    };
}

#endif //TRAFFICSIMULATOR_TRAFFICLIGHTCONTROL_H
