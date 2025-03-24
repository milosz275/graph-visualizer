#pragma once

#include <queue>
#include <vector>
#include <unordered_map>

#include "graph_algorithm.h"
#include "graph.h"

namespace mvc
{
    class bellman_ford_algorithm : public graph_algorithm
    {
    private:
        bool found_path;
        std::queue<int> path;
        int target_node;

        std::vector<float> distance;
        std::unordered_map<int, int> parent;
        int iteration;
        bool has_negative_cycle;
        int current_node;

    public:
        /**
         * @brief Creates Bellman-Ford algorithm runner marking the start node.
         * @param start_node ID of a node to start from.
         * @param target_node ID of a node to target to stop at.
         * @param nodes Reference to graph's nodes.
         */
        explicit bellman_ford_algorithm(int start_node, int target_node, std::vector<graph_node>& nodes);

        /**
         * @brief Performs one step in Bellman-Ford algorithm.
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
