//
// Created by stud on 12/28/18.
//

#include "TrafficGeneration.h"
#include "../Helpers/Visitor.h"
#include "../Helpers/Roads.h"

Ecs::Systems::TrafficGeneration::TrafficGeneration(World &world, Graph &graph, int *startpointIds,
                                                   int numberOfStartpoint) : System(world), graph(graph),
                                                                             numberOfStartpoint(numberOfStartpoint),
                                                                             startpointIds(startpointIds),
                                                                             Ticks(0) {}

void Ecs::Systems::TrafficGeneration::Update() {

    //How many should be generated should create Cause
    if (Ticks == 0) {
        auto minTicks = 10;
        auto maxTicks = 20;
        Ticks = rand() % (maxTicks - minTicks) + minTicks;
        GenerateCar();
    } else --Ticks;
}

void Ecs::Systems::TrafficGeneration::GenerateCar() {
    int endpoint = rand() % numberOfStartpoint;
    int startpoint = rand() % numberOfStartpoint;
    startpoint = (startpoint != endpoint ? startpoint : (startpoint + 1) % numberOfStartpoint);
    auto path = GetPath(graph, startpointIds[startpoint], startpointIds[endpoint]);

    auto node = path.Nodes[0];
    auto transform = world.GetComponent<Transform>(node.trafficLightEntityId);
    int pointX = transform.X + (node.entrancePoint == 0 ? 1000 : 0) + (node.entrancePoint == 2 ? -1000 : 0);
    int pointY = transform.Y + (node.entrancePoint == 1 ? -1000 : 0) + (node.entrancePoint == 3 ? 1000 : 0);
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    auto minSpeed = 10;
    auto maxSpeed = 40;
    auto speed = rand() % (maxSpeed - minSpeed) + minSpeed;
    CreateCarEntity(pointX, pointY, speed, path, Color(r, g, b));
}

void Ecs::Systems::TrafficGeneration::CreateCarEntity(int x, int y, int speed, Path path, Color color) {
    auto entity = world.CreateEntity();
    world.AddComponent(SpeedAndAcceleration(speed), entity);
    world.AddComponent(Transform(x, y, 0), entity);
    world.AddComponent(std::move(path), entity);
    world.AddComponent(Ecs::Components::Render("car", color), entity);
}

void Ecs::Systems::TrafficGeneration::OnUpdate(Entity e) {

}

Path Ecs::Systems::TrafficGeneration::GetPath(Graph g, int startpointId, int endpointId) {
    // vector for storing distance property
    std::vector<int> d(num_vertices(g));
    std::vector<Vertex> p(num_vertices(g), boost::graph_traits<Graph>::null_vertex()); //the predecessor array
    // get the first vertex
    Vertex s = *(vertices(g).first);
    // invoke variant 2 of Dijkstra's algorithm
    dijkstra_shortest_paths(g, endpointId, boost::distance_map(&d[0]).visitor(Visitor(&p[0])));

    boost::graph_traits<Graph>::vertex_iterator vi;

    Path path;

    for (int i = startpointId; i != endpointId; i = p[i]) {
        path.Nodes.emplace_back(i);
    }
    path.Nodes.emplace_back(endpointId);

    for (int j = 0; j < path.Nodes.size(); ++j) {
        int id = path.Nodes[j].trafficLightEntityId;
        auto primaryLight = world.GetComponent<Transform>(id);
        if (j != 0) {
            auto lastLight = world.GetComponent<Transform>(path.Nodes[j - 1].trafficLightEntityId);
            path.Nodes[j].entrancePoint = Roads::GetEntrypoint(lastLight.X, lastLight.Y, primaryLight.X,
                                                               primaryLight.Y);
        }

        if (j != (path.Nodes.size() - 1)) {
            auto nextLight = world.GetComponent<Transform>(path.Nodes[j + 1].trafficLightEntityId);
            path.Nodes[j].exitPoint = Roads::GetExitPoint(primaryLight.X, primaryLight.Y, nextLight.X, nextLight.Y);
        }
    }
    path.Nodes[0].entrancePoint = (path.Nodes[0].exitPoint + 2) % 4;
    path.Nodes[path.Nodes.size() - 1].exitPoint = (path.Nodes[path.Nodes.size() - 1].entrancePoint + 2) % 4;
    return path;
}