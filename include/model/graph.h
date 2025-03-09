#pragma once

#include <vector>

#include "graph_node.h"

using namespace std;

namespace mvc
{
    class graph
    {
    protected:
        vector<graph_node> nodes;
        vector<pair<int, int>> edges;
        
    public:
        
        void create_default();
        void generate_random(int num_nodes, int num_edges);
        
        // logical members (for algorithms)
        void run_algorithm_step();  // e.g., Dijkstra, BFS, etc.
        
        // physical members (for rendering)
        void draw();
        void apply_physics();
    };
}
