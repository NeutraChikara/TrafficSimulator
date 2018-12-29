//
// Created by stud on 12/28/18.
//

#ifndef TRAFFICSIMULATOR_TRAFFICGENERATION_H
#define TRAFFICSIMULATOR_TRAFFICGENERATION_H

#include "System.h"

namespace Ecs::Systems {
    class TrafficGeneration : public System {
        Graph & graph;
        int * startpointIds;
        int numberOfStartpoint;
    public:
        TrafficGeneration(World &world,Graph & graph , int * startpointIds, int numberOfStartpoint);


        void Update() override;

        void GenerateCar();

        void CreateCarEntity(int x, int y, int speed, Path path, Color color);

        Path GetPath(Graph g, int startpointId, int endpointId);

    protected:
        void OnUpdate(Entity e) override;
    };
}

#endif //TRAFFICSIMULATOR_TRAFFICGENERATION_H
