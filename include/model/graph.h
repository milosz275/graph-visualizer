#pragma once

#include <vector>

#include "graph_node.h"

namespace mvc
{
    class graph_state;

    class graph
    {
    protected:
        std::vector<graph_node> nodes;
        std::vector<std::pair<int, int>> edges;
        
    public:
        graph();
        graph(int num_nodes, bool random);
        void create_default();
        void generate_random(int num_nodes, int num_edges);
        
        // logical members (for algorithms)
        void run_algorithm_step();  // e.g., Dijkstra, BFS, etc.
        
        // physical members (for rendering)
        void draw();
        void apply_physics();

        int get_node_count();

        // overload the [] operator to access graph_node by ID
        graph_node& operator[](int id);
        const graph_node& operator[](int id) const;

        friend class graph_state;
    };
}
