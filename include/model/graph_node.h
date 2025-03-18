#pragma once

#include <vector>
#include <cmath>

namespace mvc
{
    struct graph_node
    {
        int id;
    
        // logical data (for algorithms)
        std::vector<int> neighbors;
        bool highlighted = false;
        bool visited = false;
        float distance = INFINITY;
        int parent = -1;
    
        // physical data (for rendering)
        float x, y;            // position
        float vx = 0, vy = 0;  // velocity
        float fx = 0, fy = 0;  // force accumulators
    };
}
