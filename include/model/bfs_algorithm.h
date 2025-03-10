#pragma once

#include <queue>

#include "graph_algorithm.h"
#include "graph.h"

namespace mvc
{
    class bfs_algorithm : public graph_algorithm
    {
    private:
        std::queue<int> queue;

    public:
        /**
         * @brief Creates BFS algorithm runner marking the start node.
         * @param start_node ID of a node to start from.
         */
        explicit bfs_algorithm(int start_node);
        
        /**
         * @brief Performs one step in BFS algorithm.
         * @param graph Graph reference.
         * @return Return true if waiting after print is adviced, false when the step was empty (no changes to data structures).
         */
        bool step(mvc::graph& graph) override;
        
        /**
         * @brief Returns whether queue is empty and therefore BFS algorithm is finished.
         * @return Return true if algorithm is complete, false otherwise.
         */
        bool is_complete() const override;
    };
}
