#pragma once

#include <vector>

#include "graph_node.h"

using namespace std;

namespace mvc
{
    class graph_physics
    {
    public:
        static void apply_repulsion(vector<graph_node>& nodes, float k_r);
        static void apply_attraction(vector<graph_node>& nodes, vector<pair<int, int>>& edges, float k_a, float rest_length);
        static void apply_gravity(vector<graph_node>& nodes, float k_g);
        static void update_nodes(vector<graph_node>& nodes, float time_step, float damping);
    };
}
