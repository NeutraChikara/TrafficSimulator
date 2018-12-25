//
// Created by stud on 12/25/18.
//

#ifndef TRAFFICSIMULATOR_GRAPH_H
#define TRAFFICSIMULATOR_GRAPH_H

#include "Component.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

namespace Ecs::Components {
        typedef std::pair<int, int> Edge;
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, int> > Graph;
    typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

    struct RoadGraph : Component {
        RoadGraph(std::vector<Edge> edges = {std::pair(0,0)});
        std::vector<Edge> Edges;
    };
}

#endif //TRAFFICSIMULATOR_GRAPH_H
