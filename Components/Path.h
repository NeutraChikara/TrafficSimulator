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
        Path();

        std::vector<Ecs::DataStructures::Node> Nodes;
        unsigned int IndexOfCurrentNode;
    };
}

#endif //TRAFFICSIMULATOR_PATH_H
