//
// Created by Henrik Nielsen on 15/12/2018.
//

#ifndef TRAFFICSIMULATOR_PATH_H
#define TRAFFICSIMULATOR_PATH_H


#include "Node.h"
#include "Component.h"
#include <vector>

namespace Ecs::Components {
    struct Path : Component {
        std::vector<Ecs::DataStructures::Node> Path;
        unsigned int indexOfCurrentPoint;

    };

}

#endif //TRAFFICSIMULATOR_PATH_H
