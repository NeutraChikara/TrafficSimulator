//
// Created by Henrik Nielsen on 15/12/2018.
//

#ifndef TRAFFICSIMULATOR_TRAFFICLIGHT_H
#define TRAFFICSIMULATOR_TRAFFICLIGHT_H


#include "Component.h"

namespace Ecs::Components {
    struct TrafficLight : Component {
        TrafficLight() : IsDirectionAllowed{true, false, true, false} {}

        bool IsDirectionAllowed[4];
        unsigned int LastChangedCounter;
    };
}

#endif //TRAFFICSIMULATOR_TRAFFICLIGHT_H
