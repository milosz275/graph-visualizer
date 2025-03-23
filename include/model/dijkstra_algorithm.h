#pragma once

#include <queue>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

#include "graph_algorithm.h"
#include "graph.h"

namespace mvc
{
    class dijkstra_algorithm : public graph_algorithm
    {
    private:
        bool found_path; // flag indicating the best path is found
        std::queue<int> path; // the best path constructed by the Dijkstra algorithm
        int target_node; // node to find best path from origin (node 0)

        std::set<std::pair<float, int>> processed; // (cost, node) - nodes and their costs to get to (set sorts pairs by first element - cost)
        std::vector<float> distance; // distance/cost from origin (node 0) from i-th node
        std::unordered_map<int, int> parent; // (node, parent)

    public:
        /**
         * @brief Creates Dijkstra algorithm runner marking the start node.
         * @param start_node ID of a node to start from.
         * @param target_node ID of a node to target to stop at.
         * @param nodes Reference to graph's nodes.
         */
        explicit dijkstra_algorithm(int start_node, int target_node, std::vector<graph_node>& nodes);

        /**
         * @brief Performs one step in Dijkstra algorithm.
         * @param graph Graph reference.
         * @return Return true if waiting after print is advised, false when the step was empty (no changes to data structures).
         */
        bool step(mvc::graph& graph) override;
        
        /**
         * @brief Returns whether shortest path was found and path queue is empty.
         * @return Return true if algorithm is complete, false otherwise.
         */
        bool is_complete() const override;
    };
}
