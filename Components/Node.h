//
// Created by Henrik Nielsen on 15/12/2018.
//

#ifndef TRAFFICSIMULATOR_POINT_H
#define TRAFFICSIMULATOR_POINT_H

namespace Ecs::DataStructures {

struct Node {
public:
    Node(int x,int y, int trafficLightId);
    int X,Y;
    int trafficLightEntityId;
    unsigned int entrancePoint;
};
}

#endif //TRAFFICSIMULATOR_POINT_H
