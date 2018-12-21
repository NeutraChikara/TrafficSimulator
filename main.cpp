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

#include "Components/Render.h"
#include "Managers/World.h"
#include "Systems/Logger.h"
#include "Systems/Move.h"
#include "Components/Velocity.h"
#include "Systems/Render.h"
#include "Components/Path.h"
#include "Systems/TrafficLightControl.h"
#include "Components/TrafficLight.h"
#include "Components/Node.h"
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include "Help/Visitors.h"
#include "Systems/VehicleCollisionPrevention.h"

using namespace Ecs::Components;
using namespace Ecs::Systems;
using namespace Ecs::DataStructures;

// writing out the edges in the graph
typedef std::pair<int, int> Edge;
// create a typedef for the Graph type
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

void Loop();
Graph CreateGraph(std::vector <Edge> &edges);
Path GetPath(Graph g, int startpointId, int endpointId);

static World world;
Logger logger(world);
Move move(world);
Ecs::Systems::Render render(world, Loop);
TrafficLightControl trafficLight(world);
VehicleCollisionPrevention vcp(world);

// TODO: Move path to first parameter
void CreateCarEntity(int x, int y, int vel, Path path) {
    auto entity = world.CreateEntity();
    world.AddComponent(Velocity(vel), entity);
    world.AddComponent(Transform(x, y, 0), entity);
    world.AddComponent(std::move(path), entity);
    world.AddComponent(Ecs::Components::Render("car"), entity);
}

int CreateTrafficLightEntity(int x, int y) {
    auto entity = world.CreateEntity();
    world.AddComponent(TrafficLight(), entity);
    world.AddComponent(Transform(x, y), entity);
    world.AddComponent(Ecs::Components::Render("trafficLight"), entity);
    return entity.GetId();
}

int main() {
    auto A = CreateTrafficLightEntity(-5000, 5000);
    auto B = CreateTrafficLightEntity(-5000, -5000);
    auto C = CreateTrafficLightEntity(0, 5000);
    auto D = CreateTrafficLightEntity(0, -5000);
    auto E = CreateTrafficLightEntity(5000, 5000);
    auto F = CreateTrafficLightEntity(5000, -5000);

    std::vector <Edge> edges;
    edges.emplace_back(A, C);
    edges.emplace_back(D, B);
    edges.emplace_back(C, D);
    edges.emplace_back(C, E);
    edges.emplace_back(D, F);
    edges.emplace_back(E, F);
    auto g = CreateGraph(edges);
    //CreateCarEntity(-5500, 5000, 30, GetPath(g, A, F));
    //CreateCarEntity(-6000, 5000, 45, GetPath(g, A, F));
    CreateCarEntity(5300, -5200, 30, GetPath(g, F, C));
    CreateCarEntity(5300, -5800, 45, GetPath(g, F, C));


    render.Start();
}

int GetWeight(Edge edge) {
    auto trafficlight1Transform = world.GetComponent<Transform>(edge.first);
    auto trafficlight2Transform = world.GetComponent<Transform>(edge.second);

    auto x = trafficlight1Transform.X - trafficlight2Transform.X;
    auto y = trafficlight1Transform.Y - trafficlight2Transform.Y;

    return std::sqrt(x * x + y * y);
}

Path GetPath(Graph g, int startpointId, int endpointId) {
    // vector for storing distance property
    std::vector<int> d(num_vertices(g));
    std::vector<Vertex> p(num_vertices(g), boost::graph_traits<Graph>::null_vertex()); //the predecessor array
    // get the first vertex
    Vertex s = *(vertices(g).first);
    // invoke variant 2 of Dijkstra's algorithm
    dijkstra_shortest_paths(g, endpointId, boost::distance_map(&d[0]).visitor(Visitors(&p[0])));


    std::cout << "parents in the tree of shortest paths:" << std::endl;
    for(auto vi = vertices(g).first; vi != vertices(g).second; ++vi) {
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

    for (int i = startpointId; i != endpointId  ; i = p[i]) {
        path.Nodes.emplace_back(i);
    }
    path.Nodes.emplace_back(endpointId);


    return path;
}

Graph CreateGraph(std::vector <Edge> &edges) {
    // Make convenient labels for the vertices
    const int num_vertices = edges.size();
    int weights[num_vertices];
    int j = 0;
    for (auto i = edges.begin(); i != edges.end(); ++i) {
        weights[j] = GetWeight(*i.base());
        j++;
    }
    // declare a graph object
    return Graph(&edges[0], &edges[num_vertices], weights, num_vertices);
}

void Loop() {
    logger.Update();
    trafficLight.Update();
    move.Update();
    vcp.Update();
    render.Update();
}