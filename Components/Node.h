//
// Created by Henrik Nielsen on 15/12/2018.
//

#ifndef TRAFFICSIMULATOR_POINT_H
#define TRAFFICSIMULATOR_POINT_H

namespace Ecs::DataStructures {

struct Node {
public:
    Node(int trafficLightId);
    int trafficLightEntityId;
    unsigned int entrancePoint; // TODO: Check up on entrancePoint in Move system
};
}

#endif //TRAFFICSIMULATOR_POINT_H
