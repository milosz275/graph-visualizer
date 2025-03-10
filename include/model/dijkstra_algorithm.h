#pragma once

#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "graph_algorithm.h"
#include "graph.h"

namespace mvc
{
    class dijkstra_algorithm : public graph_algorithm
    {
    private:
        std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<>> pq;
        std::unordered_set<int> processed;
        std::unordered_map<int, float> costs;
        std::unordered_map<int, int> parents;
        std::queue<int> path;

        bool found_path = false;
        int target_node = -1;

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
         * @return Return true if waiting after print is adviced, false when the step was empty (no changes to data structures).
         */
        bool step(mvc::graph& graph) override;
        
        /**
         * @brief Returns whether shortest path was found and path queue is empty.
         * @return Return true if algorithm is complete, false otherwise.
         */
        bool is_complete() const override;
    };
}
