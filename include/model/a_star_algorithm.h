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
    class a_star_algorithm : public graph_algorithm
    {
    private:
        bool found_path;
        std::queue<int> path;
        int target_node;
        
        std::set<std::pair<float, int>> open_set;
        std::vector<float> g_cost;
        std::vector<float> f_cost;
        std::unordered_map<int, int> parent;

        /**
         * @brief Calculates the Euclidean distance between two points in 2D space.
         * @param node_pos The position of the current node as a 2D vector.
         * @param goal_pos The position of the goal node as a 2D vector.
         * @return The Euclidean distance between the current node and the goal node.
         */
        float heuristic(glm::vec2 node_pos, glm::vec2 goal_pos);
    
    public:
        /**
         * @brief Creates A* algorithm runner marking the start node.
         * @param start_node ID of a node to start from.
         * @param target_node ID of a node to target to stop at.
         * @param nodes Reference to graph's nodes.
         */
        explicit a_star_algorithm(int start_node, int target_node, std::vector<graph_node>& nodes);
        
        /**
         * @brief Performs one step in A* algorithm.
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
