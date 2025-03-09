#pragma once

#include <vector>

#include "graph_node.h"

namespace mvc
{
    class graph_physics
    {
    public:
        static void apply_repulsion(std::vector<graph_node>& nodes, float k_r);
        static void apply_attraction(std::vector<graph_node>& nodes, std::vector<std::pair<int, int>>& edges, float k_a, float rest_length);
        static void apply_gravity(std::vector<graph_node>& nodes, float k_g);
        static void update_nodes(std::vector<graph_node>& nodes, float time_step, float damping);
    };
}
