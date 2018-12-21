//
// Created by Henrik Nielsen on 21/12/2018.
//

#ifndef TRAFFICSIMULATOR_VISITORS_H
#define TRAFFICSIMULATOR_VISITORS_H

#include <boost/graph/dijkstra_shortest_paths.hpp>

template<typename PredecessorMap>
class Visitors : public boost::dijkstra_visitor<> {
public:


    Visitors(PredecessorMap m_predecessor) : m_predecessor(m_predecessor) {

    }

    template<typename Edge, typename Graph>
    void edge_relaxed(Edge e, Graph &g) {
        put(m_predecessor, target(e, g), source(e, g));
    }

protected:
    PredecessorMap m_predecessor;
};


#endif //TRAFFICSIMULATOR_VISITORS_H
