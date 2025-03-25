#pragma once

#include <stack>

#include "graph_algorithm.h"
#include "graph.h"

namespace mvc
{
    class dfs_algorithm : public graph_algorithm
    {
    private:
        std::stack<std::pair<int, float>> stack;  // (node, cost)

    public:
        /**
         * @brief Creates DFS algorithm runner marking the start node.
         * @param start_node ID of a node to start from.
         */
        explicit dfs_algorithm(int start_node);

        /**
         * @brief Performs one step in DFS algorithm.
         * @param graph Graph reference.
         * @return Return true if waiting after print is advised, false when the step was empty (no changes to data structures).
         */
        bool step(mvc::graph& graph) override;

        /**
         * @brief Returns whether stack is empty and therefore DFS algorithm is finished.
         * @return Return true if algorithm is complete, false otherwise.
         */
        bool is_complete() const override;
    };
}
