#include <utility>

#include <cstdint>

/*
 * Containers algorithms and iterators ->std::for_each( TODO: use functor
 * c++11 -> lambda
 * Metaprogramming check of types in SetRequiredComponents
 * TODO: Throw Render exception hvis component mangler
 * TODO: Change CreateCarEntity to use speed instead of velocty
 * Namespaces
 */

#include <iostream>
#include "Components/Render.h"
#include "Managers/World.h"
#include "Systems/Logger.h"
#include "Systems/Drive.h"
#include "Components/SpeedAndAcceleration.h"
#include "Systems/Render.h"
#include "Components/Path.h"
#include "Systems/TrafficLight.h"
#include "Components/TrafficLight.h"
#include "Components/Node.h"
#include "Helpers/Visitor.h"
#include "Systems/VehicleCollisionPrevention.h"
#include "Components/RoadGraph.h"
#include "Helpers/Roads.h"

using namespace Ecs::Components;
using namespace Ecs::Systems;
using namespace Ecs::DataStructures;
using namespace Ecs::Helpers;


void Loop();

Graph CreateGraph(std::vector<Edge> &edges);

Path GetPath(Graph g, int startPointId, int endpointId);

static World world;
Logger logger(world);
Drive drive(world);
Ecs::Systems::Render render(world, Loop);
Ecs::Systems::TrafficLight trafficLight(world);
VehicleCollisionPrevention vcp(world);

// TODO: Move path to first parameter
void CreateCarEntity(int x, int y, int speed, Path path, Color color) {
    auto entity = world.CreateEntity();
    world.AddComponent(SpeedAndAcceleration(speed), entity);
    world.AddComponent(Transform(x, y, 0), entity);
    world.AddComponent(std::move(path), entity);
    world.AddComponent(Ecs::Components::Render("car", color), entity);
}

int CreateTrafficLightEntity(int x, int y) {
    auto entity = world.CreateEntity();
    world.AddComponent(Ecs::Components::TrafficLight(), entity);
    world.AddComponent(Transform(x, y), entity);
    world.AddComponent(Ecs::Components::Render("trafficLight", Color(0.7, 0.7, 0.7)), entity);
    return entity.GetId();
}

void CreateRoadGraphEntity(std::vector<Edge> edges) {
    auto entity = world.CreateEntity();
    world.AddComponent(RoadGraph(edges), entity);
    world.AddComponent(Transform(), entity);
    world.AddComponent(Ecs::Components::Render("roadGraph", Color(0.7, 0.7, 0.7)), entity);
}

int main() {
    auto A = CreateTrafficLightEntity(-5000, 5000);
    auto B = CreateTrafficLightEntity(-5000, -5000);
    auto C = CreateTrafficLightEntity(0, 5000);
    auto D = CreateTrafficLightEntity(0, -5000);
    auto E = CreateTrafficLightEntity(5000, 5000);
    auto F = CreateTrafficLightEntity(5000, -5000);

    std::vector<Edge> edges;
    edges.emplace_back(A, C);
    edges.emplace_back(D, B);
    edges.emplace_back(C, D);
    edges.emplace_back(C, E);
    edges.emplace_back(D, F);
    edges.emplace_back(E, F);

    auto g = CreateGraph(edges);
    CreateRoadGraphEntity(edges);

    CreateCarEntity(-5500, 5050, 30, GetPath(g, A, F), Color(0, 0, 1));
    CreateCarEntity(-6000, 5050, 35, GetPath(g, A, F), Color(1, 1, 0));
    CreateCarEntity(5800, -5000, 30, GetPath(g, F, C), Color(1, 0, 0));
    CreateCarEntity(6020, -5100, 20, GetPath(g, F, A), Color(1, 1, 0));
    CreateCarEntity(5000, 5000, 30, GetPath(g, E, A), Color(0, 0, 1));
    CreateCarEntity(-6500, 5050, 30, GetPath(g, A, E), Color(0, 0, 1));
    CreateCarEntity(-5050, -5050, 30, GetPath(g, B, C), Color(0, 0, 1));
    render.Start();
}


Path GetPath(Graph g, int startPointId, int endpointId) {
    // vector for storing distance property
    std::vector<int> d(num_vertices(g));
    std::vector<Vertex> p(num_vertices(g), boost::graph_traits<Graph>::null_vertex()); //the predecessor array
    // get the first vertex
    Vertex s = *(vertices(g).first);
    // invoke variant 2 of Dijkstra's algorithm
    dijkstra_shortest_paths(g, endpointId, boost::distance_map(&d[0]).visitor(Visitor(&p[0])));


    std::cout << "parents in the tree of shortest paths:" << std::endl;
    for (auto vi = vertices(g).first; vi != vertices(g).second; ++vi) {
        std::cout << "parent(" << *vi;
        if (p[*vi] == boost::graph_traits<Graph>::null_vertex())
            std::cout << ") = no parent" << std::endl;
        else
            std::cout << ") = " << p[*vi] << std::endl;
    }


    std::cout << "distances from start vertex:" << std::endl;
    boost::graph_traits<Graph>::vertex_iterator vi;
    for (vi = vertices(g).first; vi != vertices(g).second; ++vi)
        std::cout << d[*vi] << std::endl;
    std::cout << std::endl;

    Path path;

    for (int i = startPointId; i != endpointId; i = p[i]) {
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
    path.Nodes[0].entrancePoint = (path.Nodes[0].exitPoint+2) %4;
    path.Nodes[path.Nodes.size() -1].exitPoint = (path.Nodes[path.Nodes.size() -1].entrancePoint+2) %4;
    return path;
}

int GetWeight(Edge edge) {
    auto trafficlight1Transform = world.GetComponent<Transform>(edge.first);
    auto trafficlight2Transform = world.GetComponent<Transform>(edge.second);

    auto x = trafficlight1Transform.X - trafficlight2Transform.X;
    auto y = trafficlight1Transform.Y - trafficlight2Transform.Y;

    return std::sqrt(x * x + y * y);
}

Graph CreateGraph(std::vector<Edge> &edges) {
    const unsigned int num_vertices = edges.size();
    int weights[num_vertices];
    int j = 0;
    for (auto i = edges.begin(); i != edges.end(); ++i) {
        weights[j] = GetWeight(*i.base());
        j++;
    }

    return Graph(&edges[0], &edges[num_vertices], weights, num_vertices);
}


void Loop() {
    logger.Update();
    trafficLight.Update();
    drive.Update();
    vcp.Update();
    render.Update();
}